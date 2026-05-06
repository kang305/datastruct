#include"threadedBTree.h"
#include<stdio.h>
static ThreadedBTree *initTestTree() {
 ThreadedBTree *tree=createThreadedBTree();
    TreeNode *nodeA=createTreeNode('A');
    TreeNode *nodeB=createTreeNode('B');
    TreeNode *nodeC=createTreeNode('C');
    TreeNode *nodeD=createTreeNode('D');
    TreeNode *nodeE=createTreeNode('E');
    TreeNode *nodeF=createTreeNode('F');
    TreeNode *nodeG=createTreeNode('G');
    TreeNode *nodeH=createTreeNode('H');
    TreeNode *nodeK=createTreeNode('K');
    initThreadedBTree(tree,nodeA);
    insertTheadedBTree(tree,nodeA,nodeB,nodeE);
    insertTheadedBTree(tree,nodeB,NULL,nodeC);
    insertTheadedBTree(tree,nodeC,nodeD,NULL);
    insertTheadedBTree(tree,nodeE,NULL,nodeF);
    insertTheadedBTree(tree,nodeF,nodeG,NULL);
    insertTheadedBTree(tree,nodeG,nodeH,nodeK);
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
  *                 中序遍历:B D C A E H G K F  左子树 → 根节点 → 右子树
  */
int main() {
    ThreadedBTree *tree=initTestTree();
    printf("tree node =%d",tree->count);
    printf("\n");
    inOrderTheading(tree);
    inOrderTheadedTree(tree);
    printf("\n");
    releaseThreadedBTree(tree);
    return 0;
}