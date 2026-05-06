#ifndef DATASTRUCT2_AVLTREE_H
#define DATASTRUCT2_AVLTREE_H
typedef int element_t;
/*平衡二叉树节点结构*/
typedef struct tree_node {
    element_t data;
    struct tree_node *left;
    struct tree_node *right;
    int height;//当前节点的高度
}AVLNode;

/*平衡二叉树的树头结构*/
typedef struct {
    AVLNode *root;
    int count;
}AVLTree;

AVLTree *createAVLTree();   //创建空平衡二叉树
void releaseAVLTree(AVLTree *tree);//释放平衡二叉树
void visitAVLNode(const AVLNode *node);//访问平衡二叉树节点

void insertAVLTree(AVLTree *tree,element_t value);//平衡二叉树插入
AVLNode *searchAVLTree(const AVLTree *tree,element_t value);//在平衡二叉树中查找节点
void deleteAVLTree(AVLTree *tree, element_t value);		// 从平衡二叉树删除节点


void inOrderAVLTree(const AVLTree *tree);//平衡二叉树中序遍历
int heightAVLTree(const AVLTree *tree);//获得这棵树的高度
#endif //DATASTRUCT2_AVLTREE_H
/*
 * 类型判断
 * 失衡点的左边重or右边重
 * LL,失衡点右旋
 * LR,转换为LL,再右旋(先把R节点左旋)
 * RR,失衡点左旋
 * RL,转换为RR,再左旋(先把L节点左旋)
 */

/*
 树和森林与二叉树的转换(右子树存兄弟节点,左子树存的是孩子节点)
3.1. 树转换为二叉树
•将同一个父节点的孩子相连，水平串在一起
•保留同一个父节点的第一个孩子，其余孩子都去掉
3.2. 二叉树转换为树
• 通过任意节点的右放在一层
•将这一层向上的父节点，连接这一层的其他节点
3.3. 森林转换为二叉树
• 森林中每个树先转换为二叉树
• 将第二棵二叉树作为第一棵树的右孩事，第三棵树的根作为第二棵树的右孩子
*/

/*LR平衡操作:对R的操作左旋是对失衡点A->left这一整个子树操作(R代表新节点插在了失衡点A->leftB的右子树)
 *       A                                  A                            E
 *      / \                                / \                          / \
 *     B   C         LR->LL               E   C         LL->平衡        B   A
 *    / \           =======>             /              =====>        / \   \
 *   D   E                              B                            D   F   C
 *     /                               / \
 *    F                               D   F
 */


/*RL平衡操作:对L的操作右旋是对失衡点A->right这一整个子树操作(L代表新节点插在失衡点A->rightC的左子树)
 *        A                               A                              D
 *       / \                             / \                           /   \
 *      B   C       RL->RR              B   D        RR->平衡          A     C
 *         / \     ========>               / \      ======>          / \     \
 *        D   E                           F   C                     B   F     E
 *       /                                     \
 *      F                                       E
 *
 *
 */