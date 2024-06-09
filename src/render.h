#pragma once
#include "main.h"

struct OpenGL_Context {
  Edge* object_Window_Target; 
};


int render(Node *vertexArr, int edgeData[NUM_EDGES][2]);

Point **getVertexPos(Node *vertexArr);
