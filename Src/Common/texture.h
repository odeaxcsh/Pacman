#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string.h>

#include "defines.h"
#include "directions.h"

#include "DS/linkedlist.h"

Layer CreateEmptyLayer(int width, int height)
{
    Layer layer = (Layer) {
        .height = height,
        .width = width,
        .cells = (char **)malloc(sizeof(char *) * height)
    };
    for(int i = 0; i < height; i++) {
        layer.cells[i] = (char *)malloc(sizeof(char) * width);
        memset(layer.cells[i], '\0', width);
    }
    return layer;
}


void DrawPath(Layer layer, linkedlist directions, coord start)
{
    coord current = start;
    layer.cells[current.y][current.x] = PATH;
    for(Node *node = directions.head; node != NULL; node = node->next) {
        int direction = *(int *) node->data;
        current.x += ReverseDirections[direction].x;
        current.y += ReverseDirections[direction].y;
        layer.cells[current.y][current.x] = PATH;
    }
}

void ConstructTextLayer(Layer layer, int x, int y, const char *text)
{
    int len = strlen(text);
    for(int i = -1; i < len + 1; i++) {
        layer.cells[y - 1][x + i] = TEXT_BOX;
        layer.cells[y][x + i] = (i > -1 && i < len) ? text[i] : TEXT_BOX;
        layer.cells[y + 1][x + i] = TEXT_BOX;
    }
}

void ClearTexture(Layer *layer)
{
    for(int i = 0; i < layer->height; i++) {
        memset(layer->cells[i], '\0', layer->width);
    }
}

#endif