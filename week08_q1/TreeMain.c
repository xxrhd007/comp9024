#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"

int main(void) {
    Tree myTree;
    myTree = newTree();
    myTree = TreeInsert(myTree, 10);
    myTree = TreeInsert(myTree, 5);
    myTree = TreeInsert(myTree, 14);
    myTree = TreeInsert(myTree, 30);
    myTree = TreeInsert(myTree, 29);
    myTree = TreeInsert(myTree, 32);
//    myTree = TreeInsert(myTree, 7);
//    myTree = partition(myTree, 3);
//    myTree = rotateLeft(myTree);
    myTree = rebalance(myTree);
    showTree(myTree);
}