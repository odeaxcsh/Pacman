#ifndef _UTILIIES_H_
#define _UTILIIES_H_

#include "Common/defines.h"
#include "Common/directions.h"

void MovePacman(Table *table, int direction)
{
    coord newPacman = (coord) {
        table->pacman.x + ReverseDirections[direction].x,
        table->pacman.y + ReverseDirections[direction].y
    };
    
    table->layer->cells[table->pacman.y][table->pacman.x] = EMPTY;
    table->layer->cells[newPacman.y][newPacman.x] = PACMAN;
    table->pacman = newPacman;
}

#endif