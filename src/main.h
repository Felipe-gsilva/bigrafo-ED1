#pragma once

#define NUM_NODES 5
#define NUM_VERTEXES 7

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point point;
    int id;
} Node;

typedef struct {
    Node *from;
    Node *to;
} Vertex;
