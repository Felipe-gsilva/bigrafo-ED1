#pragma once
#include "main.h"

struct OpenGL_Context {
  Edge* object_Window_Target; 
};


int render(Node *vertexArr, Edge *edgeArr);

Point **getVertexPos(Node *vertexArr);
