// TODO: Add any extra #includes that you need
#include <stdio.h>
#include <stdlib.h> // for malloc and free etc ..
#include "queue.h"
#include <stddef.h> // for defining NULL
#include <string.h>


// TODO: Add your data structure definitions


typedef struct NodeT {
    string data;
    struct NodeT * next;
} NodeT;

//use heads and tails for the queue
typedef struct QueueRepr{
    //restore the head and the end of the queue
    NodeT* top;
    NodeT* tail;
} QueueRepr;


//good for make a new node
NodeT* makenode(string data)  {
    NodeT* new = malloc(sizeof(NodeT));
    //allocate memory for node data
    new->data = malloc(strlen(data) + 1);
    strcpy(new->data, data);
    new->next = NULL;
    return new;
}


// TODO: Fill in these function stubs

queue queue_create() {
    QueueRepr* myqueue = malloc(sizeof(QueueRepr));
    //set the top and tail to null
    myqueue->top = NULL;
    myqueue->tail = NULL;
    return myqueue;
}


void queue_destroy(queue q) {
    NodeT* curr = q->top;
    while (curr != NULL) {
        NodeT* temp = curr;
        curr = curr->next;
        //free temp data
        free(temp);
    }
    free(curr);

}


void queue_enqueue(queue q, string dat) {
    NodeT* new = makenode(dat);
    new->data = malloc(strlen(dat) + 1);
    strcpy(new->data, dat);
    new->next = NULL;
    // check if it is a empty queue
    if (q->top == NULL) {
        q->top = new;
        q->tail = new;
    }
    //put the node to the end of the queue
    else {
        q->tail->next = new;
        q->tail = new;
    }

}


string queue_dequeue(queue q) {
    // first check if q is empty:
    if (q->top == NULL) {
        return NULL;
    }
    //dequeue data from the top of the queue
    NodeT *head = q->top;
    string data = malloc(strlen(head->data) + 1);
    strcpy(data, head->data);
    q->top = q->top->next;

    // free the NodeT
    free(head);
    return data;
}





// Peeks at and returns the front element in the queue, without removing it.
string queue_peek(queue q) {
    //check if the queue is empty
    if (q == NULL || q->top == NULL) {
        return NULL;
    }
    else {
        return q->top->data;
    }
}


bool queue_empty(queue q) {

    return (q == NULL || q->top == NULL);

}
