// TODO: Add any extra #includes that you need

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// TODO: Add your data structure definitions

typedef struct NodeS {
    string data;
    struct NodeS * next;
} NodeS;

typedef struct StackRepr{
    NodeS* top;
} StackRepr;



// TODO: Fill in these function stubs

//create object:
stack stack_create() {
    StackRepr * mystack = malloc(sizeof(StackRepr));
    //in case there is wrong in malloc
    if (mystack == NULL) {
        return NULL;
    }
    mystack->top = NULL;
    return mystack;
}


void stack_destroy(stack s) {
    NodeS* curr = s->top;
    //walk through all the nodes and free them
    while (curr != NULL) {
        NodeS* temp = curr;
        curr = curr->next;
        //free auxiliary nodes
        free(temp);
    }
    free(curr);

}


void stack_push(stack s, string dat) {
    NodeS *new = malloc(sizeof(NodeS));
    //allocate memory for the data
    new->data = malloc(strlen(dat) + 1);
    strcpy(new->data, dat);
    // put the new node into the top of that
    new->next = s->top;
    s->top = new;
}


string stack_pop(stack s) {
    if (!stack_empty(s)) {
        NodeS *head = s->top;
        string t = malloc(strlen(head->data) + 1);
        if (head->data == NULL) {
            return NULL;
        }
        //allocate memory for the data
        //p points to the address of head.data
        strcpy(t, head->data);
        s->top = head->next;
        free(head);
        return t;
}
    return NULL;}


string stack_peek(stack s) {
    //pop the first node of the stack
    if (stack_empty(s)) {
        return NULL;
    }
    NodeS *head = s->top;
    string t=head->data;
    return t;
}


bool stack_empty(stack s) {
    return (s == NULL || s->top == NULL);

}
