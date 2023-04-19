#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BSTree.h"

int main(void) {
    Tree myTree;
    myTree = newTree();
    myTree = TreeInsert(myTree, 13);
    myTree = TreeInsert(myTree, 3);
    myTree = TreeInsert(myTree, 4);
    myTree = TreeInsert(myTree, 12);
    myTree = TreeInsert(myTree, 14);
    myTree = TreeInsert(myTree, 10);
    myTree = TreeInsert(myTree, 5);
    myTree = TreeInsert(myTree, 1);
    myTree = TreeInsert(myTree, 8);
    myTree = TreeInsert(myTree, 2);
    myTree = TreeInsert(myTree, 7);
    myTree = TreeInsert(myTree, 9);
    myTree = TreeInsert(myTree, 11);
    myTree = TreeInsert(myTree, 6);
    myTree = TreeInsert(myTree, 18);
    showTree(myTree);
    int height = TreeHeight(myTree);
    printf("%d", height);
    printf("\n");
    int width = TreeWidth(myTree);
    printf("%d", width);
}