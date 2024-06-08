#include <stdio.h>
#include <stdlib.h>
#include "main.h"

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

void attributeRandomNodesToVertex(Vertex *vert, Node *nodes, Node *fromNode) {
    Node *auxNode = (nodes + getRandom(NUM_NODES, 0));

    if (auxNode == fromNode) { // from e to, no Vertex, não podem ser iguais
        return attributeRandomNodesToVertex(vert, nodes, fromNode);
    }

    if (fromNode == NULL) {
        vert->from = auxNode;
    } else {
        vert->to = auxNode;
    }
}

int main() {
    Vertex *verts = malloc(sizeof(Vertex) * NUM_VERTEXES);
    Node *nodes = malloc(sizeof(Node) * NUM_NODES);
    Point *p;
    int i;

    for (i = 0; i < NUM_NODES; i++) {
        p = malloc(sizeof(Point));
        attributeRandomValuesToPoint(p);

        (nodes + i)->point = *p;

        printf("(%.2lf, %.2lf)\n", (nodes + i)->point.x, (nodes + i)->point.y);
    }

    for (i = 0; i < NUM_VERTEXES; i++) {
        attributeRandomNodesToVertex((verts + i), nodes, NULL);
        attributeRandomNodesToVertex((verts + i), nodes, (verts + i)->from);
        
        printf("(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n", (verts + i)->from->point.x, (verts + i)->from->point.y, (verts + i)->to->point.x, (verts + i)->to->point.y);
    }

    return 0;
}
