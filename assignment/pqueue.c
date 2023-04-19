// TODO: Add any extra #includes that you need

#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h> // for malloc and free etc ..
#include <stddef.h> // for defining NULL
#include <string.h>
//typedef char *string;

// TODO: Add your data structure definitions

typedef struct Node {
    string value;
    priority p;
    struct Node *next;
} NodeT;

// priority queue structure
typedef struct PriorityQueueRepr {
    NodeT *top;
} PriorityQueueRepr;



// TODO: Fill in these function stubs

pqueue pqueue_create() {
    PriorityQueueRepr* pq = malloc(sizeof(PriorityQueueRepr));
    //if malloc fails
    if (pq == NULL) {
        return NULL;
    }
    else {
        pq->top = NULL;
        return pq;
    }
}



void pqueue_destroy(pqueue pq) {
    NodeT *curr = pq->top;
    while (curr != NULL) {
        NodeT* temp = curr;
        curr = curr->next;
        //free(temp->value); // free the string value of the node
        free(temp);
    }
    free(pq);
}



void pqueue_join(pqueue queue, string value, priority prio) {
    if (queue == NULL || value == NULL) {
        return;
    }
    NodeT* new = malloc(sizeof(NodeT));
    //allocate memory for the node data
    new->value = malloc(strlen(value) + 1);
    if (new->value == NULL) {
        free(new);
        return;
    }
    strcpy(new->value, value);
    new->p = prio;
    NodeT* temp = NULL;
    NodeT* curr = queue->top;
    while (curr != NULL && curr->p < prio) {
        temp = curr;
        curr = curr->next;
    }
    // put the highest priority number at the top of the queue,thus,the lowest number
    if (temp == NULL) {
        new->next = queue->top;
        queue->top = new;
    } else {
        new->next = temp->next;
        temp->next = new;
    }
}

void update_prio(pqueue queue,string value,priority prio){
    if (queue == NULL || value == NULL) {
        return;
    }
    //remove the node firstly
    NodeT* next = NULL;
    NodeT* pre=NULL;
    NodeT *curr = queue->top;
    while (curr != NULL&&curr->value != value) {
        pre= curr;
        curr = curr->next;
        next=curr->next;
    }
    free(curr);
    pre->next=next;
    free(pre);
    free(next);
    pqueue_join(queue,value,prio);

    }




 //Removes the highest priority string in the given pqueue.


//from the top
string pqueue_leave(pqueue queue) {
    if (queue == NULL || queue->top == NULL) {
        return NULL;
    }
    NodeT* node = queue->top;
    queue->top = node->next;
    string value = node->value;
    free(node);
    return value;
}





string pqueue_peek(pqueue pq) {
    
    if (pq == NULL || pq->top == NULL) {
        return NULL;
    }
    else {
        return pq->top->value;
    }
}





bool pqueue_empty(pqueue pq) {
    return (pq == NULL || pq->top == NULL);
}
