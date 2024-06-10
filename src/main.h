#pragma once

#define NUM_NODES 5
#define NUM_EDGES 5

#define WHITE 0
#define RED 1
#define BLUE -1

#define VAR_DIST 0.01

typedef struct {
    float x;
    float y;
    float color;
} Coord;
