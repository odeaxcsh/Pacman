#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include <string.h>

#include "Common/DS/linkedlist.h"

#include "Common/directions.h"
#include "Common/defines.h"
#include "Common/colors.h"

#include "Game/characters.h"
#include "Game/theme.h"

/**
 * this function returns a ASCII character for a given block according to the
 * blocks around of it.
 * for example:
 * block = (UP | DOWN | LEFT) means that there are obstecles at upper and lower block
 * so the character will be ASCII 186 or '╣'
*/
char BlockToChar(int block)
{
    switch (block)
    {
        case NONE:  return 254; // ascII '■'

        case UP: case DOWN: case UP | DOWN: return 186; // ascII '║'
        
        case LEFT: case RIGHT: case LEFT | RIGHT: return 205; // ascII '═'
        
        case UP | LEFT: return 188; // ascII '╝'

        case UP | RIGHT: return 200; // ascII '╚'

        case DOWN | LEFT: return 187; // ascII '╗'
        
        case DOWN | RIGHT: return 201; // ascII '╔'
        
        case UP | LEFT | RIGHT: return 202; // ascII '╩'

        case DOWN | LEFT | RIGHT: return 203; // ascII '╦'

        case UP | DOWN | RIGHT: return 204; // ascII '╠'

        case UP | DOWN | LEFT: return 185; // ascII '╣'
        
        case UP | DOWN | LEFT | RIGHT: return 206; // ascII '╬'

    default:
        return '?';
    }
}

char FlimentChar(Layer layer, int x, int y, int p)
{
    const int block = GetBlockValue(
		x+1 < layer.width ? layer.cells[y][x+1] == p : 0,
		x > 0 ? layer.cells[y][x-1] == p : 0,
		y+1 < layer.height ? layer.cells[y+1][x] == p : 0,
		y > 0 ? layer.cells[y-1][x] == p : 0
	);

    return BlockToChar(block);
}

char GetCellChar(Layer table, int x, int y)
{
    int cell = table.cells[y][x];
    switch(cell) {
        case PACMAN:
            return PACMAN_CHAR;
        case GHOST:
            return GHOST_CHAR;
        case FRUIT:
            return FRUIT_CHAR;
        case WALL:
            return FlimentChar(table, x, y, WALL);
        case PATH:
            return FlimentChar(table, x, y, PATH);
        case TEXT_BOX:
            return FlimentChar(table, x, y, TEXT_BOX);
        case EMPTY:
            return ' ';
        default:
            if(isalpha(cell) || isdigit(cell) || isspace(cell)) {
                return cell;
            } else {
                return '?';
            }   
    }
}

Color GetCellColor(Layer table, int x, int y)
{
    int cell = table.cells[y][x];
    switch(cell) {
        case PACMAN:
            return PACMAN_COLOR;
        case GHOST:
            return GHOST_COLOR;
        case FRUIT:
            return FRUIT_COLOR;
        case WALL:
            return WALL_COLOR;
        case EMPTY:
            return EMPTY_COLOR;
        case PATH:
            return PATH_COLOR;
        case TEXT_BOX:
            return TEXT_COLOR;
        default:
            if(isalpha(cell) || isdigit(cell) || isspace(cell)) {
                return TEXT_COLOR;
            } else {
                return ERROR_COLOR;
            }
    }
}

#endif