// Starting code for Dijkstra's algorithm ... COMP9024 22T2

#include <stdio.h>
#include <stdbool.h>
#include "PQueue.h"

#define VERY_HIGH_VALUE 999999

void dijkstraSSSP(Graph g, Vertex source) {
    int  dist[MAX_NODES];
    int  pred[MAX_NODES];
    bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
    int s;

    PQueueInit();
    int nV = numOfVertices(g);
    for (s = 0; s < nV; s++) {
        joinPQueue(s);
        dist[s] = VERY_HIGH_VALUE;
        pred[s] = -1;
        vSet[s] = true;
    }
    dist[source] = 0;
    pred[source] = source;

    /* NEEDS TO BE COMPLETED */
    for (int i = 0; i < nV; i++) {
        if (vSet[i] == true) {
            int minD = leavePQueue(dist);
            for (int j = 0; j < nV; ++j) {
                if (adjacent(g, minD, j) != 0) {
                    if (dist[minD] + adjacent(g, minD, j) < dist[j]) {
                        dist[j] = dist[minD] + adjacent(g, minD, j);
                        pred[j] = minD;
                    }
                }
            }
            vSet[i] = false;
        }
    }

    for (int j = 0; j < nV; ++j) {
        if (dist[j] == VERY_HIGH_VALUE) {
            printf("%d: no path", j);
        } else {
            printf("%d: distance = %d, shortest path:", j, dist[j]);
            int path[nV];
            for (int k = 0; k < nV; ++k) {
                path[k] = -1;
            }
            int final = j;
            path[0] = final;
            if (final != source) {
                for (int k = 1; k < nV; ++k) {
                    if (pred[final] != source) {
                        path[k] = pred[final];
                        final = path[k];
                    } else {
                        path[k] = source;
                        break;
                    }
                }
            }

            for (int k = nV - 1; k >=0; --k) {
                if (path[k] != -1) {
                    if (path[k] == source) {
                        printf("%d", path[k]);
                    } else {
                        printf("-%d", path[k]);
                    }
                }
            }
        }
        printf("\n");
    }
}

void reverseEdge(Edge *e) {
    Vertex temp = e->v;
    e->v = e->w;
    e->w = temp;
}

int main(void) {
    Edge e;
    int  n, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1) {
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight);
        insertEdge(g, e);
        reverseEdge(&e);               // ensure to add edge in both directions
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");
    dijkstraSSSP(g, source);
    freeGraph(g);
    return 0;
}