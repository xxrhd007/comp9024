// TODO: Add any extra #includes that you need

#include "pagerank.h"
#include "dijkstra.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h> // for malloc and free etc ..
#include <stddef.h> // for defining NULL
#include <string.h>
#include <stdbool.h>
#include <stdbool.h>
#include <math.h>
#include "stack.h"
#define VERY_HIGH_VALUE 99999


// TODO: Add your data structure definitions

typedef struct Vertex {
    string name;
    struct Edge *edges;
    //number of edges
    size_t number;
} Vertex;

//because of it is a adjacency list,so the next appears in the edge
typedef struct Edge {
    Vertex *des;
    weight w;
    struct Edge *next;
} Edge;


typedef struct GraphRepr {
    Vertex **v;
    size_t num_v;
    double *pRank;
    double *oRank;
    weight *dist;
    size_t *pred;
    int *vSet;
} GraphRepr;


//help find where eh vertex exists
static Vertex *find(graph g, string name) {
    for (size_t i = 0; i < g->num_v; i++) {
        if (strcmp(g->v[i]->name, name) == 0) {
            return g->v[i];
        }
    }
    return NULL;
}



// TODO: Fill in these function stubs
graph graph_create(void) {
    GraphRepr * g = malloc(sizeof(GraphRepr));
    //initialize vertex and number of vertex
    g->v = NULL;
    g->num_v = 0;
    return g;
}


void graph_destroy(graph g) {
    //if g is empty
    if (g == NULL) {
        return;
    }
    for (size_t i = 0; i < g->num_v; i++) {
        Vertex *v = g->v[i];
        Edge *e = v->edges;
        while (e != NULL) {
            Edge *temp = e->next;
            //free edges
            free(e);
            e = temp;
        }
        //free vertex.
        free(v->name);
        free(v);
    }
    free(g->v);
    free(g);
}


void graph_add_vertex(graph g, string v) {
    // check if the vertex already exists
    if (find(g, v) != NULL) {
        return;
    }
    // create a new vertex
    Vertex *new = malloc(sizeof(Vertex));
    new->name = malloc(strlen(v) + 1);
    strcpy(new->name, v);
    new->edges = NULL;
    new->number = 0;
//join the vertex to the graph
//increase the memory to g->numv+1
    g->v = realloc(g->v, (g->num_v + 1) * sizeof(Vertex));
    g->v[g->num_v] = new;
    g->num_v++;
}


bool graph_has_vertex(graph g, string v) {
    return (find(g, v) != NULL);
}



size_t graph_vertices_count(graph g) {
    return g->num_v;
}


void graph_add_edge(graph g, string v1, string v2, weight w) {
//the source node
    Vertex *vertex1 = find(g, v1);
//the destination of edge
    Vertex *vertex2 = find(g, v2);

    //wrong case
    if (vertex1 == NULL || vertex2 == NULL) {
        return;
    }
    if(graph_has_edge(g,v1,v2)) {
        return;
    }else{
        Edge *new = malloc(sizeof(Edge));
        new->des = vertex2;
 //weight
        new->w = w;
        new->next = NULL;

        // if there is no edge
        if (vertex1->edges == NULL) {
            vertex1->edges = new;
        } else {
            Edge *curr = vertex1->edges;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = new;
        }
        vertex1->number++;

    }
    // create a new edge with the given weight

}




bool graph_has_edge(graph g, string v1, string v2) {
    Vertex *vertex1 = find(g, v1);
    Vertex *vertex2 = find(g, v2);
    if (vertex1 == NULL || vertex2 == NULL) {
        return false;
    }

    Edge *edge = vertex1->edges;
    while (edge != NULL) {
        if (edge->des == vertex2) {
            return true;
        }
        edge = edge->next;
    }
    return false;
}



void graph_update_edge(graph g, string v1, string v2, weight w) {
 //check if has this edge
    if(graph_has_edge(g,v1,v2)){
        Vertex *vertex1 = find(g, v1);
        Edge *edge = vertex1->edges;
        while (edge != NULL) {
            //update weight
            if (strcmp(edge->des->name, v2) == 0) {
                 edge->w=w;
            }
            edge = edge->next;
    }
    }else{
        //create new edge
        graph_add_edge(g, v1, v2, w);
    }
}



weight graph_get_edge(graph g, string v1, string v2) {
    Vertex *vertex1 = find(g, v1);

    Edge *edge = vertex1->edges;
    while (edge != NULL) {
        if (strcmp(edge->des->name, v2) == 0) {
            return edge->w;
        }
        edge = edge->next;
    }
//if there is no edge,return high value
    return VERY_HIGH_VALUE;
}






void graph_show(graph g, FILE *output) {
    if (g == NULL) {
        return;
    }
    // print the v
    for (size_t i = 0; i < g->num_v; i++) {
        fprintf(output, "%s\n", g->v[i]->name);
    }
    // print the edges
    for (size_t i = 0; i < g->num_v; i++) {
        Vertex *temp = g->v[i];
        Edge *edge = temp->edges;
        while (edge!= NULL) {
            fprintf(output, "%s %s %.3lf\n", temp->name, edge->des->name, edge->w);
            edge = edge->next;
        }
    }
}
size_t graph_edges_count(graph g, string v) {
    // TODO: Delete the code below when you're ready to implement this function
    Vertex *vertex=find(g,v);
     size_t count=0;
     //count inbound
     for(size_t i=0;i<g->num_v;i++){
         if(graph_has_edge(g,g->v[i]->name,v)){
             count=count+1;
         }
     }
     //inbound + outbound
     count=count+vertex->number;
     return count;

}

//follow the pesudocode ,no comment lol
void graph_pagerank(graph g, double damping, double delta) {
    // TODO: Delete the code below when you're ready to implement this function
    int num = graph_vertices_count(g);
    g->oRank = calloc(num, sizeof(double));
    g->pRank = calloc(num, sizeof(double));

    for (size_t i = 0; i < g->num_v; ++i) {
        g->oRank[i] = 0;
        g->pRank[i] = 1.0 / num;
    }
    for (int j = 0; j < num; ++j) {
        while (fabs(g->pRank[j] - g->oRank[j]) > delta) {
            for (size_t i = 0; i < g->num_v; ++i) {
                g->oRank[i] = g->pRank[i];

            }
            double sink_rank = 0;
            for (size_t i = 0; i < g->num_v; ++i) {
                if (g->v[i]->number==0) {
                    sink_rank = sink_rank + (damping * (g->oRank[i] / num));
                    }

            }
            for (size_t i = 0; i < g->num_v; ++i) {
                g->pRank[i] = sink_rank + ((1 - damping) / num);
                for (size_t k = 0; k < g->num_v; ++k) {
                    if (graph_has_edge(g, g->v[k]->name, g->v[i]->name) == true) {
                        g->pRank[i] = g->pRank[i] + ((damping * g->oRank[k]) / g->v[k]->number);
                            }
                        }
                    }
                }
    }
        
    
}

void graph_show_pagerank(graph g, FILE *file) {
    // TODO: Delete the code below when you're ready to implement this function
    int index[g->num_v];
    int temp;
    double temp1;
    for (size_t i = 0; i < g->num_v; ++i) {
        index[i] = i;
    }
    for (size_t i = 0; i < g->num_v;++i) {
        for (size_t j = 0; j < g->num_v - i - 1; ++j) {
            if (g->pRank[j] < g->pRank[j + 1]) {
                temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;

                temp1 = g->pRank[j];
                g->pRank[j] = g->pRank[j + 1];
                g->pRank[j + 1] = temp1;
            }
        }
    }
    if (!file) {
        for (size_t i = 0; i < g->num_v; ++i) {
            fprintf(stdout,"%s (%.3lf)\n", g->v[index[i]]->name, g->pRank[i]);

        }
    } else {
        for (size_t i = 0; i < g->num_v; ++i) {
            fprintf(file,"%s (%.3lf)\n", g->v[index[i]]->name, g->pRank[i]);
        }
    }
}

void graph_worst_path(graph g, string source, double damping, double delta) {
    // TODO: Delete the code below when you're ready to implement this function
    graph_pagerank(g, damping, delta);
    //update the weight to the pagerank
    for (size_t i = 0; i < g->num_v; i++) {
        for (size_t j = 0; j < g->num_v; j++) {
            if (graph_has_edge(g, g->v[j]->name, g->v[i]->name)) {
                graph_update_edge(g, g->v[j]->name, g->v[i]->name, g->pRank[i]);
            }
        }
    }
    int index=0;
    //restore weight
    g->dist = calloc(g->num_v, sizeof(weight));
    //restore previous node
    g->pred = calloc(g->num_v,sizeof(size_t));
    //mark the experienced node
    g->vSet = calloc(g->num_v, sizeof(int));
    size_t count = 0;//count the number that already have the shortest path
    for (size_t i = 0; i < g->num_v; i++)    //初始化
    {
        if (strcmp(g->v[i]->name,source)==0) {
            index = i;
        }
    }
    for (size_t i = 0; i < g->num_v; i++)    //initialize dist,pred,vset
    {
        if (graph_has_edge(g, source, g->v[i]->name)) {
            g->dist[i] = graph_get_edge(g, source, g->v[i]->name);
            g->pred[i] = index;
        }else if(strcmp(g->v[i]->name,source)==0){
            g->vSet[i] = 1;
            g->pred[i] = i;
            g->dist[i]=0;
       }else{
            g->dist[i]=VERY_HIGH_VALUE;
            g->pred[i]=-1;
        }}

    count++;
//    for (int i = 0; i < g->num_v; i++) {
//        printf("%f", g->dist[i]);
//    }}
    while (count < g->num_v) {
        weight min = VERY_HIGH_VALUE;
        int target_index=0;
        //find minist distence
        for (size_t i = 0; i < g->num_v; i++) {
            if (g->vSet[i] == 0 && min > g->dist[i])         //找到距离源点最短的顶点target_index
            {
                min = g->dist[i];
                target_index = i;
            }
        }
        g->vSet[target_index] = 1;

        count++;
        for (size_t i = 1; i < g->num_v; i++) {
            if (g->vSet[i] == 0 && g->dist[target_index] +
                                   graph_get_edge(g, g->v[target_index]->name, g->v[i]->name) <
                                   g->dist[i])            //update edge
            {
                g->dist[i] = g->dist[target_index] + graph_get_edge(g, g->v[target_index]->name, g->v[i]->name);
                g->pred[i] = target_index;
            }
        }
    }}


void graph_show_path(graph g, string destination) {
    //use stack to restore previous nodes
    stack s = stack_create();
    size_t dindex=0;
    size_t sindex=0;
    size_t signal=-1;
    if (graph_has_vertex(g, destination)) {
        for (size_t i = 0; i < g->num_v; ++i) {
            if (strcmp(g->v[i]->name, destination) == 0) {
                dindex = i;
            }
            if (g->pred[i] == i) {
                sindex = i;
            }
        }
    }
//-1 means no previous node
    if (g->pred[dindex] == signal) {
        printf("No path found.");
    } else {//untill found the source node
        printf("%s", g->v[sindex]->name);
        printf("\n");
        stack_push(s, g->v[dindex]->name);
        while (g->pred[dindex] != sindex) {
            stack_push(s, g->v[g->pred[dindex]]->name);
            dindex = g->pred[dindex];
        }
        while (!stack_empty(s)) {
            string pre = stack_pop(s);
            printf("-> %s", pre);
            printf("\n");
        }
    }
}



















