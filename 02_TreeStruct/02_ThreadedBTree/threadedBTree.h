#ifndef DATASTRUCT2_THREADEDBTREE_H
#define DATASTRUCT2_THREADEDBTREE_H
/*一个二叉树如果有n个节点,就有n+1个空位置*/
/*递归:怎么进来,按原来返回*/
/*线索二叉树*/
/*处理顺序:左子树 → 根节点 → 右子树(中序遍历)*/
typedef char element_t;
/*线索二叉树的节点结构*/
typedef struct tree_node {
    struct tree_node* left;   //左指针:指向左孩子或前驱线索
    struct tree_node* right;  //右指针:指向右孩子或后继线索
    element_t data;
    int l_tag;//左标志.0表示指向左子树,1表示指向前驱节点(0是实线指向,1是虚线指向)
    int r_tag;//右标志.0表示指向右子树,1表示指向后继节点(0是实线指向,1是虚线指向)
}TreeNode;
/*线索二叉树树头结构*/
typedef struct {
    TreeNode* root;
    int count;
}ThreadedBTree;

ThreadedBTree *createThreadedBTree();
void releaseThreadedBTree(ThreadedBTree *tree);
void initThreadedBTree(ThreadedBTree *tree,TreeNode* root);
TreeNode* createTreeNode(element_t data);
void visitTreeNode(const TreeNode *node);
void insertTheadedBTree(ThreadedBTree* tree,TreeNode *parent,TreeNode* left,TreeNode* right);

//在原始树中构建线索
void inOrderTheading(ThreadedBTree* tree);
//在已经线索化好的二叉树中,进行中序遍历(非递归)
void inOrderTheadedTree(ThreadedBTree* tree);
#endif //DATASTRUCT2_THREADEDBTREE_H
/*对于任意节点 node，在中序遍历中：
* 它的前驱节点：左子树中最后被访问的节点（如果左子树为空，则是更上层的某个节点）。
* 它的后继节点：右子树中第一个被访问的节点（如果右子树为空，则是更上层的某个节点）。
 */