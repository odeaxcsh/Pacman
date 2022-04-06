#ifndef _COUT_H_
#define _COUT_H_

#include <stdio.h>

#include "utilities.h"
#include "directions.h"
#include "terminal.h"
#include "represent.h"
#include "maps.h"

void PutChar(char c, Color color)
{
    ChangeColor(color);
    printf("%c", c);
}

void PutCharOfTable(const Layer *layer, int x, int y)
{
    char cell = GetCellChar(*layer, x, y);
    Color color = GetCellColor(*layer, x, y);
    PutChar(cell, color);
}

void PrintTexture(const Layer *main, const Layer *filler, int pause_time)
{
    for (int y = 0; y < main->height; y++) {
        for (int x = 0; x < main->width; x++) {
            if(filler && filler->cells[y][x]) {
                PutCharOfTable(filler, x, y);
            } else if(main) {
                PutCharOfTable(main, x, y);
            }
            Pause(pause_time);
        }
        printf("\n");
    }
}

void UpdateCell(Layer *layer, int x, int y, coord origin)
{
    GotoXY(origin.x + x, origin.y + y);
    PutCharOfTable(layer, x, y);
}

void UpdatePacmanInScreen(Table table, coord oldPacman, coord origin)
{
    UpdateCell(table.layer, oldPacman.x, oldPacman.y, origin);
    UpdateCell(table.layer, table.pacman.x, table.pacman.y, origin);
}

void MovePacmanByPath(Table *table, linkedlist path, coord origin)
{
    for(Node *node = path.head; node != NULL; node = node->next) {
        int direction = *(int *) node->data;
        coord oldPacman = table->pacman;
        MovePacman(table, direction);
        UpdatePacmanInScreen(*table, oldPacman, origin);
        Pause(MOVE_SLEEP_TIME);
    }
}

Table *LoadInfo(FILE *file)
{
    Table *table = (Table *)malloc(sizeof(Table));
    Layer *layer = (Layer *)malloc(sizeof(Layer));
    
    char c;
    fscanf(file, "%d %d\n", &layer->width, &layer->height);

    int width = 0;
    while((c = fgetc(file)) != '\n') {
        width++;
    }

    char *row = (char *)malloc(sizeof(char) * width + 1);
    int i = 1;
    while(!feof(file)) {
        ++i;
        fscanf(file, "%s\n", row);
        if(strlen(row) != width) {
            printf("[Error] Length of %dth row is not equal to width (%d)\n", i, width);
            return NULL;
        }
    }
    free(row);

    layer->height = i;
    layer->width = width;
    table->layer = layer;
    return table;
}

Table *ReadTable(const char *fileName)
{

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File not found\n");
        return NULL;
    }

    Table *table;
    if((table = LoadInfo(file)) == NULL) {
        return NULL;
    }

    Layer *layer = table->layer;

    fseek(file, 0, SEEK_SET);

    char ch;
    layer->cells = (char **)malloc(layer->height * sizeof(char *));
    for (int y = 0; y < layer->height; y++) {
        layer->cells[y] = (char *)malloc(layer->width * sizeof(char));
        for (int x = 0; x < layer->width; x++) {
            fscanf(file, "%c", &ch);
            layer->cells[y][x] = FromMapToTable(ch);

            if(layer->cells[y][x] == -1) {
                printf("[Warning] Invalid character %c[%d] at (%d, %d)\n", ch, ch, x, y);
                return NULL;
            }

            if(layer->cells[y][x] == PACMAN) {
                table->pacman = (coord) { x, y };
            } else if(layer->cells[y][x] == GHOST) {
                coord ghost = (coord) { x, y };
                linkedlist_append_value(&table->ghosts, coord, ghost);
            } else if(layer->cells[y][x] == FRUIT) {
                coord fruit = (coord) { x, y };
                linkedlist_append_value(&table->fruits, coord, fruit);
            }
        }
        fscanf(file, "\n");
    }

    table->layer = layer;
    return table;
}

#endif