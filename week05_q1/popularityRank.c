// Graph ADT
// Adjacency Matrix Representation ... COMP9024 22T2
#include "WGraph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
typedef struct GraphRep {
    int  **edges;   // adjacency matrix
    int    nV;      // #vertices
    int    nE;      // #edges
} GraphRep;

bool isnumber(char *word) {
    if (strspn(word, "0123456789") == strlen(word)) {
        return true;
    } else {
        return false;
    }
}

void sort(float * a, int length, int* b)
{
    int i, j, t1;
    float t;
    for(j = 0; j < length; j++)
        for(i = 0; i < length - 1 - j; i++)
            if(a[i]<a[i + 1])
            {
                t=a[i];
                a[i]=a[i + 1];
                a[i + 1]=t;


                t1=b[i];
                b[i]=b[i + 1];
                b[i + 1]=t1;
            }

}


void analyseDegree(Graph g) {
    int inDegree[g->nV];
    for (int dd = 0; dd < g->nV; ++dd) {
        inDegree[dd] = 0;
    }

    int outDegree[g->nV];
    for (int dd = 0; dd < g->nV; ++dd) {
        outDegree[dd] = 0;
    }

    for (int i = 0; i < g->nV; ++i) {
        for (int j = 0; j < g->nV; ++j) {
            if (g->edges[i][j] != 0) {
                outDegree[i] += 1;
                inDegree[j] += 1;
            }
        }
    }

    float popuLarity[g->nV];
    for (int dd = 0; dd < g->nV; ++dd) {
        popuLarity[dd] = 0;
    }
    for (int j = 0; j < g->nV; ++j) {
        if (outDegree[j] != 0) {
            popuLarity[j] = 1.0 * inDegree[j] / outDegree[j];
        } else {
            popuLarity[j] = 1.0 * inDegree[j] / 0.5;
        }
    }

    printf("Popularity ranking:\n");

    int index[g->nV];
    for (int dd = 0; dd < g->nV; ++dd) {
        index[dd] = dd;
    }

    sort(popuLarity, g->nV, index);
    for (int i = 0; i < g->nV; ++i) {
        printf("%d %.1f\n", index[i], popuLarity[i]);
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
                myEdge.weight = myEdge.v + myEdge.w;
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
    printf("\n");
    analyseDegree(myGraph);
    freeGraph(myGraph);
}