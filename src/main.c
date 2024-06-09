#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include <time.h>

int getRandom(int ceil, int floor) {
  return (rand() % ceil) + floor;
}

void attributeRandomCoord(Coord *coord) {
  coord = malloc(sizeof(Coord));
  coord->x = getRandom(20000, -10000) / 10000.0; // max=1, min=-1
  coord->y = getRandom(20000, -10000) / 10000.0;
  coord->color = 0.0;
}

void addRandomEdge(int matAdj[NUM_NODES][NUM_NODES]) {
  int u = getRandom(NUM_NODES, 0);
  int v = getRandom(NUM_NODES, 0);

  if (u == v) {
    return addRandomEdge(matAdj);
  }

  if (matAdj[u][v] != 0) {
    return addRandomEdge(matAdj);
  }

  matAdj[u][v] = 1;
}

int main() {
  srand(time(NULL));
  int i, edgeIndex[NUM_EDGES][2];
  int index = 0;
  int grafo[NUM_NODES][NUM_NODES];
  Coord *coord = malloc(sizeof(Coord) * NUM_NODES);

  for (int i = 0; i < NUM_NODES; i++) {
    for (int j = 0; j < NUM_NODES; j++) {
      grafo[i][j] = 0;
    }
  }

  for (i = 0; i < NUM_NODES; i++) {
    attributeRandomCoord(&coord[i]);
  }

  for (i = 0; i < NUM_EDGES; i++) {
    addRandomEdge(grafo);
  }

  for (int i = 0; i < NUM_NODES; i++) {
    for (int j = 0; j < NUM_NODES; j++) {
      printf("%d\t", grafo[i][j]);
    }
      printf("\n");
  }

  for (int i = 0; i < NUM_NODES; i++) {
    for (int j = 0; j < NUM_NODES; j++) {
      if (grafo[i][j] != -1) {
        edgeIndex[index][0] = i;
        edgeIndex[index++][1] = j;
      }
    }
  }

  for (int i = 0; i < NUM_EDGES; i++) {
    printf("%d ", edgeIndex[i][0]);
    printf("%d\n", edgeIndex[i][1]);
  }

  if (isBigraph(grafo)) {
    printf("E bigrafo! :)\n");
  } else {
    printf("Nao e bigrafo :(\n");
  }
  
  if(render(grafo, edgeIndex)!= 0)
    return -1;
  
  return 0;
}
