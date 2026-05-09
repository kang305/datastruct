#include <stdio.h>
#include "RBTree.h"

int main() {
    int data[] = {55, 40, 65, 60, 75, 57, 63, 56};
    RBTree *rbTree = createRBTree();
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        insertRBTree(rbTree, data[i]);
    }
    if (rbTree->root) {
        printRBTree(rbTree->root, rbTree->root->key, 0);
    }
    printf("\n");
    deleteRBTree(rbTree, 63);
    printRBTree(rbTree->root, rbTree->root->key, 0);
    return 0;
}
