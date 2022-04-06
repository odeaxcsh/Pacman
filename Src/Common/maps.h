#ifndef _MAPS_H_
#define _MAPS_H_

#include "defines.h"

#define PACMAN_IN_MAP '0'
#define FRUIT_IN_MAP '*'
#define EMPTY_IN_MAP '1'
#define WALL_IN_MAP '#'
#define GHOST_IN_MAP 'G'

int FromMapToTable(char cell)
{
    switch (cell)
    {
    case PACMAN_IN_MAP:
        return PACMAN;
    case FRUIT_IN_MAP:
        return FRUIT;
    case EMPTY_IN_MAP:
        return EMPTY;
    case WALL_IN_MAP:
        return WALL;
    case GHOST_IN_MAP:
        return GHOST;
    default:
        return -1;
    }
}

#endif