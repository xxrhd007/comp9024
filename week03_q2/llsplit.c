#include <assert.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct node {
    int data;
    struct node *next;
} NodeT;

NodeT *makeNode(int v) {
    NodeT *new = malloc(sizeof(NodeT));
    assert(new != NULL);
    new->data = v;       // initialise data
    new->next = NULL;    // initialise link to next node
    return new;          // return pointer to new node
}

NodeT *insertLL(NodeT *list, int d) {
    NodeT *new = makeNode(d);  // create new list element
    new->next = list;          // link to beginning of list
    return new;                // new element is new head
}

NodeT *joinLL(NodeT *list, int v) {
    NodeT *head;
    NodeT *new = makeNode(v);
    head = list;
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = new;
    return list;
}

void freeLL(NodeT *list) {
    NodeT *p, *temp;

    p = list;
    while (p != NULL) {
        temp = p->next;
        free(p);
        p = temp;
    }
}

void showLL(NodeT *list) {
    NodeT *p;
    for (p = list; p != NULL; p = p->next)
        if (p->next != NULL){
            printf("%d-->", p->data);
        } else {
            printf("%d", p->data);
        }
    printf("\n");
}

void splitLL(NodeT *list) {
    NodeT *s, *f, *list2;

    s = list;
    f = list->next;

    while (f != NULL && f->next != NULL) {
        s = s->next;
        f = f->next->next;
    }
    list2 = s->next;
    if (list2!= NULL){
        s->next = NULL;
        printf("First part is ");
        showLL(list);
        printf("Second part is ");
        showLL(list2);
    } else {
        printf("First part is ");
        showLL(list);
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
    char w[BUFSIZ];
    NodeT *myList;
    printf("Enter an integer: ");
    scanf("%s", w);
    if (isnumber(w)) {
        int numFirst = atoi(w);
        myList = makeNode(numFirst);
        do {
            printf("Enter an integer: ");
            scanf("%s", w);
            if (isnumber(w)) {
                int num = atoi(w);
                myList = joinLL(myList, num);
            } else {
                printf("Done. List is ");
                showLL(myList);
                splitLL(myList);
                freeLL(myList);
            }
        } while (isnumber(w));
    } else {
        printf("Done.");
    }



}


