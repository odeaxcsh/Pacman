#ifndef _DIRECTIONS_H_
#define _DIRECTIONS_H_

#include "Common/defines.h"

#define RIGHT   8   // 0b1000
#define LEFT    4   // 0b0100
#define DOWN    2   // 0b0010
#define UP      1   // 0b0001
#define NONE    0   // 0b0000

const int DirectionsCount = 4;
coord Directions[] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

coord ReverseDirections[] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};


int GetBlockValue(int right, int left, int down, int up)
{
    return (right * RIGHT) + (left * LEFT) + (down * DOWN) + (up * UP);
}

#endif