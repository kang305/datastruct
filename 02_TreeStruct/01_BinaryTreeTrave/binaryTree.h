#ifndef DATASTRUCT2_BINARYTREE_H
#define DATASTRUCT2_BINARYTREE_H
/*递归:怎么进来,按原来返回*/
typedef char element_t;
//二叉树的节点结构
typedef struct tree_node {
    struct tree_node* left;
    struct tree_node* right;
    element_t data;
}TreeNode;
//二叉树的树头结构
typedef struct {
    TreeNode* root;
    int cnt;
}BinaryTree;
/*任意二叉树的接口*/
BinaryTree *createBinaryTree();//申请树头结构
void releaseBinaryTree(BinaryTree *tree);//释放
void initBinaryTree(BinaryTree *tree,TreeNode *root);//初始化树头
TreeNode* createTreeNode(element_t data);//产生树节点
void insertBinaryTree(BinaryTree *tree,TreeNode *parent,TreeNode* left,TreeNode* right);//插入
void visitBinaryTree(const TreeNode *node);//访问查看


//广度遍历
void levelOrderBTree(const BinaryTree *tree);
//深度遍历,一直走直到走不动,返回,处理另外一条路径(递归)
void preOrderBTree(const BinaryTree *tree);//先序遍历
void inOrderBTree(const BinaryTree *tree);//中序遍历
void postOrderBTree(const BinaryTree *tree);//后序遍历
//深度遍历(非递归)
void preOrderBTreeV2(const BinaryTree *tree);//先序遍历
void inOrderBTreeV2(const BinaryTree *tree);//中序遍历
void postOrderBTreeV2(const BinaryTree *tree);//后序遍历
#endif //DATASTRUCT2_BINARYTREE_H



/*时间复杂度计算核心思想:循环次数与数据规模的关系
 *(1)终止条件
 *(2)找循环次数和循环终止变量的关系
 *(3)和n的关系
 *一.一重循环,循环次数,数据规模之间的关系
 *1.终止条件
 *2找循环次数和循环终止变量的关系
 *3.等式联立,推导关系
 *二.二重循环,循环次数,数据规模之间的关系
 *1.外层循环的执行次数
 *2.内层循环的执行次数,构成二维矩阵
 *3.二维矩阵的节点数量就是循环次数
 */