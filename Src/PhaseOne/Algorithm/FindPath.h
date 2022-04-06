#ifndef _FIND_PATH_H_
#define _FIND_PATH_H_

#include "Common/DS/linkedlist.h"
#include "Common/directions.h"
#include "Common/defines.h"

linkedlist FindPath(Map costs, coord start)
{
    linkedlist directions = linkedlist_create();

    coord current = start;
    int cost = costs.cells[current.y][current.x];

    if(cost == INF) {
        return directions;
    }

    while(cost > 0) {
        int next_cost = cost - 1;
        
        for(int i = 0; i < DirectionsCount; ++i) {
            coord next = (coord) {
                current.x + Directions[i].x,
                current.y + Directions[i].y
            };
            if(costs.cells[next.y][next.x] == next_cost) {
                linkedlist_append_value(&directions, int, i);
                current = next;
                cost = next_cost;
                break;
            }
        }
    }
    linkedlist_reverse(&directions);
    return directions;
}

#endif