#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <limits.h>
#include "DS/linkedlist.h"

#define INF INT_MAX

#define BUFFER_MAX_LEN (1024)

#define EMPTY       0
#define WALL        1
#define PACMAN      2
#define FRUIT       3
#define PATH        4
#define GHOST       5
#define TEXT_BOX    6


typedef struct {
    int x;
    int y;
} coord;

typedef struct {
    int width, height;
    char **cells;
} Layer;

void ClearLayer(Layer layer)
{
    for (int i = 0; i < layer.height; i++) {
        free(layer.cells[i]);
    }
    free(layer.cells);
}

typedef struct {
    int width, height;
    int **cells;
} Map;

void ClearMap(Map map)
{
    for (int i = 0; i < map.height; i++) {
        free(map.cells[i]);
    }
    free(map.cells);
}

typedef struct {
    Layer *layer;
    coord pacman;
    linkedlist fruits;
    linkedlist ghosts;
} Table;

void FreeTable(Table *table)
{
    ClearLayer(*table->layer);
    free(table->layer);
    linkedlist_clear(&table->fruits);
    linkedlist_clear(&table->ghosts);
    free(table);
}

#endif