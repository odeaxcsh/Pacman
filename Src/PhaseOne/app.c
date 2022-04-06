#include "phase.h"

#include "Common/io.h"
#include "Common/defines.h"
#include "Common/terminal.h"
#include "Common/texture.h"
#include "Common/Algorithm/BFS.h"
#include "Common/utilities.h"
#include "Common/CLI.h"
#include "Algorithm/FindPath.h"


int nearest_first(const void *a, const void *b, void *context)
{    
    Map *map = (Map *) context;
    const coord *ac = (coord *)a;
    const coord *bc = (coord *)b;    
    
    return map->cells[ac->y][ac->x] - map->cells[bc->y][bc->x];
}

int main()
{
    InitTerminal();

    const char *map_file = GetFileName(&IsFileValid);
    Table *table;
    if((table = ReadTable(map_file)) == NULL) {
        printf("Error: Invalid map file.\n");
        return 1;
    }

    coord screenOrigin = GetXY();
    Layer text = CreateEmptyLayer(table->layer->width, table->layer->height);
    ConstructTextLayer(text, table->layer->height/2, 5, "Printing");
    PrintTexture(&text, NULL, 0);
    GotoXY(screenOrigin.x, screenOrigin.y);
    PrintTexture(table->layer, &text, 0);
    GotoXY(screenOrigin.x, screenOrigin.y);
    PrintTexture(table->layer, NULL, 0);


    HideCursor();
    Map costs = BFS(table->layer, table->pacman, WALL);
    linkedlist fruits_order = linkedlist_sort(table->fruits, &nearest_first, &costs);
    while(fruits_order.size != 0) {
        GotoXY(screenOrigin.x, screenOrigin.y);
        Pause(CHOOSE_SLEEP_TIME);

        coord *fruit = (coord *) linkedlist_pop_value(&fruits_order);
        Map costs = BFS(table->layer, table->pacman, WALL);
        linkedlist path = FindPath(costs, *fruit);
        Layer path_layer = CreateEmptyLayer(table->layer->width, table->layer->height);

        DrawPath(path_layer, path, table->pacman);
        PrintTexture(&path_layer, table->layer, 0);

        MovePacmanByPath(table, path, screenOrigin);

        linkedlist_clear(&path);
    }

    GotoXY(screenOrigin.x, screenOrigin.y);
    ShowCursorIcon();
    ClearTexture(table->layer);
    PrintTexture(table->layer, NULL, 5);

    FreeTable(table);
    ClearLayer(text);
    ClearMap(costs);
    linkedlist_clear(&fruits_order);
    printf("[Program Finished]\n");
    return 0;
}