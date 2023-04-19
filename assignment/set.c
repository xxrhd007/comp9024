// TODO: Add any extra #includes that you need

#include "set.h"
#include <stdio.h>
#include <stdlib.h> // for malloc and free etc ..
#include <stddef.h> // for defining NULL
#include <string.h>

// TODO: Add your data structure definitions

typedef struct NodeT {
    string data;
    struct NodeT * next;
} NodeT;


typedef struct SetRepr{
    NodeT* top;
} SetRepr;



// TODO: Fill in these function stubs

set set_create() {
    SetRepr* new = malloc(sizeof(SetRepr));
    //set empty top
    new->top = NULL;
    return new;
}


void set_destroy(set s) {
    NodeT* curr = s->top;
    //loop to free set
    while (curr != NULL) {
        NodeT*  temp= curr->next;
        free(curr);
        curr = temp;
    }
    
    free(s);
}


void set_insert(set s, string dat) {
    //  need to know if set contains the item
    if (!set_contains(s, dat)) {
        NodeT* new= malloc(sizeof(NodeT));
        new->data = malloc(strlen(dat) + 1);
        strcpy(new->data, dat);
        new->next = s->top;
        s->top = new;
    }
}


void set_remove(set s, string dat) {
    //use temp to record the previous node of the node to delete
    NodeT* curr = s->top;
    NodeT* temp = NULL;
    while (curr != NULL) {
        if (strcmp(curr->data, dat) == 0) {
            // if the node at the top of the set
            if (temp == NULL) {
                s->top = curr->next;
                //link the previous and the next node of the current node
            } else {
                temp->next = curr->next;
            }
            free(curr->data);
            free(curr);
 
            break;
        }
        temp = curr;
        curr = curr->next;
    }
}

//check every node's data
bool set_contains(set s, string dat) {
    NodeT* curr = s->top;
    while (curr != NULL) {
        if (strcmp(curr->data, dat) == 0) { //if we have reached the dat
            return true;
        }
        curr = curr->next;
    }
    return false;
}

