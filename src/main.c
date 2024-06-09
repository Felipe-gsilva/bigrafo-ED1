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

int EdgeHas(Edge *edges, Edge v, int currSize) {
  for (int i = 0; i < currSize; i++) {
    if ( // Compara os enderecos de nodes (n sei se funciona msm)
      ((edges + i)->to == v.from && (edges + i)->from == v.to) ||
      (edges + i)->from == v.to && (edges + i)->to == v.from
    ) {
      return 1;
    }
  }

  return 0;
}

int findToNode(Node *nodes, ) {

}

void attributeRandomNodesToEdge(Edge *edges, int i, Node *nodes, Node *fromNode) {
  Node *auxNode = (nodes + getRandom(NUM_NODES, 0));

  if (auxNode == fromNode) { // from e to, no Edge, não podem ser iguais
    return attributeRandomNodesToEdge(edges, i, nodes, fromNode);
  }

  if (EdgeHas(edges, *(edges + i), i)) { // Garante que o grafo vai ser digrafo
    return attributeRandomNodesToEdge(edges, i, nodes, fromNode);
  }

  if (fromNode == NULL) {
    (edges + i)->from = auxNode;
  } else {
    (edges + i)->to = auxNode;
  }
}

int isBigraph(Edge *verts, Node *nodes) {
  int *visited = malloc(sizeof(int) * NUM_NODES);
  int i;
  Node *curr = nodes + 0; // 0 é o nó source

  for (i = 0; i < NUM_NODES; i++) {
    visited[i] = 0;
  }

  visited[curr->id]++;

  while(1) {
    verts
  }
}

void attributeGraphs(Edge *mainVertArr, Edge *leftEdgeSet, Edge *rightNodeSet) {
    
}

int main() {
  Node *nodes = malloc(sizeof(Node) * NUM_NODES);

  Edge *edges = malloc(sizeof(Edge) * NUM_EDGES);
  Edge *leftEdgeSet = malloc(sizeof(Edge) * ceil(NUM_EDGES / 2));
  Edge *rightEdgeSet = malloc(sizeof(Edge) * ceil(NUM_EDGES / 2));

  Point *p;

  int i;

  for (i = 0; i < NUM_NODES; i++) {
    p = malloc(sizeof(Point));
    attributeRandomValuesToPoint(p);

    (nodes + i)->point = *p;
    (nodes + i)->id = i;

    printf("(%.2lf, %.2lf)\n", (nodes + i)->point.x, (nodes + i)->point.y);
  }

  for (i = 0; i < NUM_EDGES; i++) {
    attributeRandomNodesToEdge(edges, i, nodes, NULL);
    attributeRandomNodesToEdge(edges, i, nodes, (edges + i)->from);

    printf("(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n", (edges + i)->from->point.x, (edges + i)->from->point.y, (edges + i)->to->point.x, (edges + i)->to->point.y);
  }

  isBigraph(edges, nodes);
  if(render(edges))
    return 0;
  return -1;
}
