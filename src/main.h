#pragma once

#include <stdbool.h>

#define NUM_NODES 5
#define NUM_EDGES 7

typedef struct {
    double x;
    double y;
    double color;
} Point;

typedef struct {
    Point point;
    int id;
} Node;

typedef struct {
    Node *from;
    Node *to;
} Edge;
