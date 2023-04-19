#include "IntQueue.h"
#include "assert.h"

typedef struct {
    int item[MAXITEMS];
    int top;
    int bottom;
} queueRep;

static queueRep queueObject;

void QueueInit() {
    queueObject.top = -1;
    queueObject.bottom = 0;
}        // set up empty queue


int  QueueIsEmpty() {
    return (queueObject.top < queueObject.bottom);
}    // check whether queue is empty


void QueueEnqueue(int n) {
    assert(queueObject.top < MAXITEMS-1);
    queueObject.top++;
    int i = queueObject.top;
    queueObject.item[i] = n;
}  // insert int at end of queue

int  QueueDequeue() {
    assert(queueObject.bottom <= queueObject.top);
    int i = queueObject.bottom;
    int n = queueObject.item[i];
    queueObject.bottom++;
    return n;
}   // remove int from front of queue

