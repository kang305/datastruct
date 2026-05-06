#include<stdio.h>
#include"binaryTree.h"

static BinaryTree *initTestTree() {
    BinaryTree *tree=createBinaryTree();
    TreeNode *nodeA=createTreeNode('A');
    TreeNode *nodeB=createTreeNode('B');
    TreeNode *nodeC=createTreeNode('C');
    TreeNode *nodeD=createTreeNode('D');
    TreeNode *nodeE=createTreeNode('E');
    TreeNode *nodeF=createTreeNode('F');
    TreeNode *nodeG=createTreeNode('G');
    TreeNode *nodeH=createTreeNode('H');
    TreeNode *nodeK=createTreeNode('K');
    initBinaryTree(tree,nodeA);
    insertBinaryTree(tree,nodeA,nodeB,nodeE);
    insertBinaryTree(tree,nodeB,NULL,nodeC);
    insertBinaryTree(tree,nodeC,nodeD,NULL);
    insertBinaryTree(tree,nodeE,NULL,nodeF);
    insertBinaryTree(tree,nodeF,nodeG,NULL);
    insertBinaryTree(tree,nodeG,nodeH,nodeK);
    return tree;
}
/*
  *                                     A
  *                                   /   \
  *                                  B     E
  *                                   \     \
  *                                    C     F
  *                                   /     /
  *                                  D     G
  *                                       / \
  *                                      H   K
  *      先序遍历:A B C D E F G H K  根节点 → 左子树 → 右子树
  *      中序遍历:B D C A E H G K F  左子树 → 根节点 → 右子树
  *      后序遍历:D C B H K G F E A  左子树 → 右子树 → 根节点
  */
void test01(){
     BinaryTree *tree=initTestTree();
     printf("tree cnt:%d\n",tree->cnt);
    levelOrderBTree(tree);
    printf("\n");
    preOrderBTree(tree);
    printf("\n");
    inOrderBTree(tree);
    printf("\n");
    postOrderBTree(tree);
    printf("\n");
    releaseBinaryTree(tree);
}

void test02() {
    BinaryTree *tree=initTestTree();
    printf("tree cnt:%d\n",tree->cnt);
    levelOrderBTree(tree);
    printf("\n");
    preOrderBTreeV2(tree);
    printf("\n");
    inOrderBTreeV2(tree);
    printf("\n");
    postOrderBTreeV2(tree);
    printf("\n");
    releaseBinaryTree(tree);
}
int main() {
    test01();
    test02();
    return 0;
}