//
// Created by 1 on 2023/4/12.
//
#include <stdio.h>
#include "graph.c"
#include "dijkstra.h"

int main() {
    graph g = graph_create();
    graph_add_vertex(g, "A");
    graph_add_vertex(g, "B");
    graph_add_vertex(g, "C");
    graph_add_vertex(g, "D");
    graph_add_edge(g, "A", "B", 1.0);
    graph_add_edge(g, "A", "C", 2.0);
    graph_add_edge(g, "B", "D", 3.0);
    graph_add_edge(g, "C", "D", 1.0);



    double damping = 0.85;
    double delta = 0.0001;
    graph_worst_path(g, "B", damping, delta);
//    for(int i=0;i<g->num_v;i++){
//        printf("%d  ", g->pred[i]);
//        //printf("%f  ", g->pRank[i]);
//    }
//    printf("%d  ", g->pred[3]);
//    //printf("%d", graph_get_vertex(g,"D"));
//    printf("%f", graph_get_edge(g,"A","B"));
    graph_show_path(g, "C");
    //printf("%s", g->v[3]->name);

    graph_destroy(g);
    return 0;
}