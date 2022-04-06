#ifndef _BFS_H_
#define _BFS_H_

#include "Common/directions.h"
#include "Common/defines.h"
#include "Common/DS/linkedlist.h"

Map createEmptyMap(Layer *layer)
{
    Map map = (Map) {
        .width = layer->width,
        .height = layer->height,
        .cells = (int **) malloc(sizeof(int *) * layer->height)
    };

    for(int i = 0; i < layer->height; i++) {
        map.cells[i] = (int *) malloc(sizeof(int) * layer->width);
        for(int j = 0; j < layer->width; j++) {
            map.cells[i][j] = INF;
        }
    }

    return map;
}

Map BFS(Layer *map, coord start, int barrier)
{
    Map shortest_path = createEmptyMap(map);
    linkedlist queue = linkedlist_create();

    shortest_path.cells[start.y][start.x] = 0;
    linkedlist_append_value(&queue, coord, start);

    while(queue.size) {
        coord *current = (coord *) linkedlist_pop_value(&queue);
        int current_distance = shortest_path.cells[current->y][current->x];

        for(int i = 0; i < 4; i++) {
            coord next = (coord) {
                .x = current->x + Directions[i].x,
                .y = current->y + Directions[i].y
            };

            if(next.x < 0 || next.x >= map->width || next.y < 0 || next.y >= map->height) {
                continue;
            }

            if(map->cells[next.y][next.x] == barrier) {
                continue;
            }

            if(shortest_path.cells[next.y][next.x] == INF) {
                shortest_path.cells[next.y][next.x] = current_distance + 1;
                linkedlist_append_value(&queue, coord, next);
            }
        }
        free(current);
    }

    linkedlist_clear(&queue);
    return shortest_path;
}

#endif