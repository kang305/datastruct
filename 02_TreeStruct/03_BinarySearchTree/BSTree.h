#ifndef DATASTRUCT2_BSTREE_H
#define DATASTRUCT2_BSTREE_H
/*递归:怎么进来,按原来返回*/
typedef int element_t;
/*定义二叉搜索树的节点*/
typedef struct bsNode {
    element_t data;
    struct bsNode* left;
    struct bsNode* right;
}BSNode;

/*定义二叉搜索树的树结构*/
typedef struct {
    BSNode* root;
    int count;
}BSTree;

BSTree* createBSTree();//创建树结构
void releaseBSTree(BSTree* tree);//释放树


//按照二叉搜索树的规则插入数据(递归)
void insertBSTreeV1(BSTree* tree, element_t e);
// 按照二叉搜索树的规则插入数据（非递归方式）
void insertBSTreeV2(BSTree* tree, element_t e);
//查找二叉搜索树里值为e的节点
BSNode* searchBSTree(const BSTree* tree, element_t e);
// 按照二叉搜索树的规则删除数据（递归方式）
void deleteBSTreeV1(BSTree* tree, element_t e);
// 按照二叉搜索树的规则删除数据（非递归方式）
void deleteBSTreeV2(BSTree* tree, element_t e);

//中序排序的遍历接口
void visitBSNode(const BSNode *node);//访问
int heightBSTree(const BSTree* tree);//高度
void inOrderBSTree(const BSTree* tree);//中序遍历



/*测试BST前序与后序遍历*/
void preOrderBSTree(const BSTree *tree);
void PostOrderBSTree(const BSTree *tree);
#endif //DATASTRUCT2_BSTREE_H
/*
 * 度为0:直接删除
 * 度为1:把有数据的位置进行替换
 */
/*度为2
 * 后继节点:右边的最小值,右边的极左
 * 前驱节点:左边的最大值,左边的极右
 * 替换度为2的点,把删除任务转换为删除后继或前驱(度为0或1)
 */



