// Graph ADT
// Adjacency Matrix Representation ... COMP9024 22T2
#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
typedef struct GraphRep {
    int  **edges;   // adjacency matrix
    int    nV;      // #vertices
    int    nE;      // #edges
} GraphRep;


void analyseDgree(Graph g) {
    assert(g != NULL);
    int i, j;
    int d[g->nV];
    for (int dd = 0; dd < g->nV; ++dd) {
        d[dd] = 0;
    }

    for (i = 0; i < g->nV; i++)
        for (j = i+1; j < g->nV; j++)
            if (g->edges[i][j]) {
                d[i] += 1;
                d[j] += 1;
            }

    int miniDegree = d[0];
    for (int k = 0; k < g->nV; ++k) {
       if (d[k] < miniDegree) {
           miniDegree = d[k];
       }
    }
    printf("Minimum degree: %d\n", miniDegree);

    int maxDegree = d[0];
    for (int k = 0; k < g->nV; ++k) {
        if (d[k] > maxDegree) {
            maxDegree = d[k];
        }
    }
    printf("Maximum degree: %d\n", maxDegree);

    printf("Nodes of minimum degree: \n");
    for (int k = 0; k < g->nV; ++k) {
        if (d[k] == miniDegree) {
            printf("%d\n", k);
        }
    }

    printf("Nodes of maximum degree: \n");
    for (int k = 0; k < g->nV; ++k) {
        if (d[k] == maxDegree) {
            printf("%d\n", k);
        }
    }

    printf("Triangles:\n");
    for (int k = 0; k < g->nV; k++) {
        if (d[k] >=2) {
            for (int l = k+1; l < g->nV; l++) {
                if (adjacent(g, k, l) == true) {
                    for (int m = l+1; m < g->nV; m++) {
                        if (adjacent(g, l, m) == true) {
                            if (adjacent(g, m, k) == true) {
                                printf("%d-%d-%d\n", k, l, m);
                            }
                        }
                    }
                }
            }
        }
    }
}



bool isnumber(char *word) {
    if (strspn(word, "0123456789") == strlen(word)) {
        return true;
    } else {
        return false;
    }
}


int main(void) {
    int a;
    char v1[BUFSIZ];
    char v2[BUFSIZ];
    GraphRep *myGraph;

    printf("Enter the number of vertices: ");
    scanf("%d", &a);
    myGraph = newGraph(a);

   do {
        Edge myEdge;
        printf("Enter an edge (from): ");
        scanf("%s", v1);
        if (isnumber(v1)) {
            myEdge.v = atoi(v1);
            printf("Enter an edge (to): ");
            scanf("%s", v2);
            if (isnumber(v2)) {
                myEdge.w = atoi(v2);
            } else {
                printf("Done.\n");
                break;
            }
        } else {
            printf("Done.\n");
            break;
        }
        insertEdge(myGraph, myEdge);
    } while (isnumber(v1) && isnumber(v2));

    analyseDgree(myGraph);
}