#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "window.h"


int getRandom(int ceil, int floor) {
  return (rand() % ceil) + floor;
}

/**
 * Atribui x e y para o endereco do ponto p
 * (x, y) = (93.83, 8.86)
 */
void attributeRandomValuesToPoint(Point *p) {
  p->x = getRandom(10000, 0) / 100.0;
  p->y = getRandom(10000, 0) / 100.0;
}

int vertexHas(Vertex *vertArr, Vertex v, int currSize) {
  for (int i = 0; i < currSize; i++) {
    if ( // Compara os enderecos de nodes (n sei se funciona msm)
      ((vertArr + i)->to == v.from && (vertArr + i)->from == v.to) ||
      (vertArr + i)->from == v.to && (vertArr + i)->to == v.from
    ) {
      return 1;
    }
  }

  return 0;
}

void attributeRandomNodesToVertex(Vertex *vertArr, int i, Node *nodes, Node *fromNode) {
  Node *auxNode = (nodes + getRandom(NUM_NODES, 0));

  if (auxNode == fromNode) { // from e to, no Vertex, não podem ser iguais
    return attributeRandomNodesToVertex(vertArr, i, nodes, fromNode);
  }

  if (vertexHas(vertArr, *(vertArr + i), i + 1)) { // Garante que o grafo vai ser digrafo
    return;
  }

  if (fromNode == NULL) {
    (vertArr + i)->from = auxNode;
  } else {
    (vertArr + i)->to = auxNode;
  }
}

int isBigraph(Vertex *verts) {

}

void attributeGraphs(Vertex *mainVertArr, Vertex *leftVertexSet, Vertex *rightVertexSet) {
    
}

int main() {
  Node *nodes = malloc(sizeof(Node) * NUM_NODES);

  Vertex *verts = malloc(sizeof(Vertex) * NUM_VERTEXES);
  Vertex *leftVertexSet = malloc(sizeof(Vertex) * ceil(NUM_VERTEXES / 2));
  Vertex *rightVertexSet = malloc(sizeof(Vertex) * ceil(NUM_VERTEXES / 2));

  Point *p;

  int i;

  for (i = 0; i < NUM_NODES; i++) {
    p = malloc(sizeof(Point));
    attributeRandomValuesToPoint(p);

    (nodes + i)->point = *p;

    printf("(%.2lf, %.2lf)\n", (nodes + i)->point.x, (nodes + i)->point.y);
  }

  for (i = 0; i < NUM_VERTEXES; i++) {
    attributeRandomNodesToVertex(verts, i, nodes, NULL);
    attributeRandomNodesToVertex(verts, i, nodes, (verts + i)->from);

    printf("(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n", (verts + i)->from->point.x, (verts + i)->from->point.y, (verts + i)->to->point.x, (verts + i)->to->point.y);
  }

  render();

  return 0;
}
