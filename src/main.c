#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "render.h"
#include <time.h>

int getRandom(int ceil, int floor) {
  return (rand() % ceil) + floor;
}

// Checa se x está VAR_DIST ou menos proximo de y
int isClose(double x, double y) {
  return (fabs(x - y) <= VAR_DIST) && (fabs(x - y) >= -VAR_DIST) ? 1 : 0;
}

void attributeRandomCoord(Coord *coords, int i) {
  double x = getRandom(20000, -10000) / 10000.0; // max=1, min=-1
  double y = getRandom(20000, -10000) / 10000.0; // max=1, min=-1
  
  for (int j = 0; j < i; j++) {
    if (isClose(coords[j].x, x) && isClose(coords[j].y, y)) {
      return attributeRandomCoord(coords, i);
    }
  }

  coords[i].x = x;
  coords[i].y = y;
  coords[i].color = WHITE;
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

int isBigraph(int edgeIndex[NUM_EDGES][2], Coord *coords) {
  int queue[NUM_NODES], visited[NUM_NODES], colors[NUM_NODES];
  int i, qi, qend, curr;

  for (i = 0; i < NUM_NODES; i++) {
    queue[i] = -1;
    visited[i] = 0;
    colors[i] = WHITE; // 0
  }

  qi = 0;
  qend = 0;
  queue[qend++] = edgeIndex[0][0];
  visited[edgeIndex[0][0]] = 1; // comeco
  colors[edgeIndex[0][0]] = 1;

  while (qi < qend) {
    curr = queue[qi++]; // pop

    for (i = 0; i < NUM_EDGES; i++) {
      if (edgeIndex[i][0] == curr && !visited[edgeIndex[i][1]]) {
        queue[qend++] = edgeIndex[i][1]; // adiciona no adjacente na fila
        visited[edgeIndex[i][1]] = 1; // marca esse no como visitado
        colors[edgeIndex[i][1]] = -colors[curr]; // coloca a cor oposta
      } else if (edgeIndex[i][1] == curr && !visited[edgeIndex[i][0]]) {
        queue[qend++] = edgeIndex[i][0];
        visited[edgeIndex[i][0]] = 1;
        colors[edgeIndex[i][0]] = -colors[curr];
      }
    }
  }

    for (i = 0; i < NUM_EDGES; i++) { // retorna 0 se nao e bipartido
      if (colors[edgeIndex[i][0]] == colors[edgeIndex[i][1]]) {
        return 0;
      }
    }

    for (i = 0; i < NUM_NODES; i++) { // coloca cor
      coords[i].color = colors[i];
    }

    return 1;
}

int main() {
  srand(time(NULL));
  int i, edgeIndex[NUM_EDGES][2];
  int index = 0;
  int matAdj[NUM_NODES][NUM_NODES];
  Coord *coords = malloc(sizeof(Coord) * NUM_NODES);

  for (int i = 0; i < NUM_NODES; i++) {
    for (int j = 0; j < NUM_NODES; j++) {
      matAdj[i][j] = 0;
    }
  }

  for (i = 0; i < NUM_EDGES; i++) {
    addRandomEdge(matAdj);
  }

  for (int i = 0; i < NUM_NODES; i++) {
    for (int j = 0; j < NUM_NODES; j++) {
      printf("%d\t", matAdj[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < NUM_NODES; i++) {
    for (int j = 0; j < NUM_NODES; j++) {
      if (matAdj[i][j] != 0 && i != j) {
        edgeIndex[index][0] = i;
        edgeIndex[index++][1] = j;
      }
    }
  }

  for (int i = 0; i < NUM_NODES; i++) {
    attributeRandomCoord(coords, i);
  }
  
  for (i = 0; i < NUM_EDGES; i++) {
    printf("%d %d\n", edgeIndex[i][0], edgeIndex[i][1]);
  }

  if (isBigraph(edgeIndex, coords)) {
    printf("E bigrafo! :)\n");
  } else {
    printf("Nao e bigrafo :(\n");
  }

  for (int i = 0; i < NUM_NODES; i++) {
    printf("color: %.1f\n", coords[i].color);
  }

  if(render(coords, edgeIndex)!= 0)
    return -1;
  
  return 0;
}
