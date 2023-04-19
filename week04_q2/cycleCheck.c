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

/*int visited[1001];
bool dfsCycleCheck(Graph g, Vertex v, int ss) {
    visited[v] = 1;
    for (int i = 0; i < g->nV; ++i) {
        if (adjacent(g, v, i)) {
            if (visited[i] == 0) {
                if (dfsCycleCheck(g, i,v)) {
                    return true;
                }
            } else if (i!=ss) {
                return true;
            }
        }
    }
    return false;
}*/

int visited[1001];
bool dfsCycleCheck(Graph g, Vertex v, int ss) {
    visited[v] = 1;
    for (int i = 0; i < g->nV; ++i) {
        if (adjacent(g, v, i)) {
            if (visited[i] == 1) {
                if (i!=ss) {
                    return true;
                }
            } else if (dfsCycleCheck(g, i,v)) {
                return true;
            }
        }
    }
    return false;
}

/*int visited[1001];
bool dfsCycleCheck(Graph g, Vertex v) {
    visited[v] = 1;
    for (int i = v+1; i < g->nV; ++i) {
        if (adjacent(g, v, i)) {
            if (visited[i] == 1) {
                return true;
            } else if (dfsCycleCheck(g, i)) {
                return true;
            }
        }
    }
    return false;
}*/


int hasCycle(Graph g) {
    int flag = 0;
    for (int i = 0; i < g->nV; ++i) {
        if (dfsCycleCheck(g, i, i)) {
            flag = 1;
            break;
        } else {
            for (int j = 0; j < 1001; ++j) {
                visited[j] = 0;
            }
        }
    }
    return flag;
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

    if (hasCycle(myGraph)) {
        printf("The graph has a cycle.");
    } else {
        printf("The graph is acyclic.");
    }

}