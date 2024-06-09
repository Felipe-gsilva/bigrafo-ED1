#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "render.h"
#include <time.h>

int getRandom(int ceil, int floor) {
  return (rand() % ceil) + floor;
}

void attributeRandomCoord(Coord *coord) {
  coord->x = getRandom(20000, -10000) / 10000.0; // max=1, min=-1
  coord->y = getRandom(20000, -10000) / 10000.0; // max=1, min=-1
  coord->color = 0.0;
}

void addRandomEdge(int matAdj[NUM_NODES][NUM_NODES]) {
  int u = getRandom(NUM_NODES, 0);
  int v = getRandom(NUM_NODES, 0);
  int temp;

  if (u > v) {
    temp = u;
    u = v;
    v = temp;
  }

  if (u == v) {
    return addRandomEdge(matAdj);
  }

  if (matAdj[u][v] != 0) {
    return addRandomEdge(matAdj);
  }

  matAdj[u][v] = 1;
}

int isBigraph(int mat[NUM_NODES][NUM_NODES], Coord *coords) {
  int color[NUM_NODES], queue[NUM_NODES];
  int i, front, rear, u, v;

  for (i = 0; i < NUM_NODES; i++) {
    color[i] = 0;
  }

  for (i = 0; i < NUM_NODES; i++) {
    if (color[i] != 0) {
      continue;
    }

    color[i] = 1;
    front = 0;
    rear = 0;
    queue[rear++] = i;

    while (front != rear) {
      u = queue[front++];
      for (v = 0; v < NUM_NODES; v++) {
        if (mat[u][v] == 1 && color[v] == 0) {
          color[v] = -color[u];
          queue[rear++] = v;
        } else if (mat[u][v] == 1 && color[u] == color[v]) {
          return 0;
        }
      }
    }
  }

  for (int i = 0; i < NUM_NODES; i++) {
    if (coords[i].color != 1 && coords[i].color != -1) {
      coords[i].color = (color[i] == 1) ? 1 : -1;
    }
  }
  return 1;
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
      if (grafo[i][j] != 0 && i != j) {
        edgeIndex[index][0] = i;
        edgeIndex[index++][1] = j;
      }
    }
  }

  for (int i = 0; i < NUM_NODES; i++) {
    attributeRandomCoord(&coord[i]);
  }

  if (isBigraph(grafo, coord)) {
    printf("E bigrafo! :)\n");
  } else {
    printf("Nao e bigrafo :(\n");
  }

  for (int i = 0; i < NUM_NODES; i++) {
    printf("%lf\n", coord[i].color);
  }

  if(render(coord, edgeIndex)!= 0)
    return -1;
  
  return 0;
}
