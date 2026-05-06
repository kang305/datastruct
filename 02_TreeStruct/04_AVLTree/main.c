#include "AVLTree.h"
#include <stdio.h>
void testAVLTree() {
    AVLTree* tree=createAVLTree();
    element_t values[]={30,20,40,10,25,35,50,5};
    for(int i=0;i<sizeof(values)/sizeof(values[0]);i++) {
        insertAVLTree(tree,values[i]);
    }
    //验证是否是二叉搜索树
    inOrderAVLTree(tree);
    printf("\n");
    //验证是否是二叉平衡树
    printf("\tthe tree height= %d\n",heightAVLTree(tree));
    element_t searchTestValue[]={25,100};
    for(int i=0;i<sizeof(searchTestValue)/sizeof(searchTestValue[0]);i++) {
        AVLNode *result=searchAVLTree(tree,searchTestValue[i]);
        if(result!=NULL) {
            printf("Found %d in the tree\n",searchTestValue[i]);
        }else {
            printf("Not found %d in the tree\n" ,searchTestValue[i]);
        }
    }
    deleteAVLTree(tree,10);
    inOrderAVLTree(tree);
    printf("\n");
    printf("\tthe tree height= %d\n",heightAVLTree(tree));
    deleteAVLTree(tree,30);
    inOrderAVLTree(tree);
    printf("\n");
    printf("\tthe tree height= %d\n",heightAVLTree(tree));
    releaseAVLTree(tree);
}

int main() {
testAVLTree();

    return 0;
}
/*
 *
 *
 *
 *
 *
 *
 *
 */