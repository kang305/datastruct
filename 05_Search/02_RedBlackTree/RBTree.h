#ifndef DATASTRUCT2_RBTREE_H
#define DATASTRUCT2_RBTREE_H
enum  RBColor{RED,BLACK};
typedef int KeyType;
/*红黑树的节点结构*/
typedef struct rb_Node {
    char color;
    KeyType key;
    struct rb_Node* parent;//用于找叔叔节点
    struct rb_Node* left;
    struct rb_Node* right;
}RBNode;
/*红黑树的树头结构*/
typedef struct {
    RBNode* root;
    int count;
}RBTree;

//产生红黑树
RBTree *createRBTree();
//释放红黑树
void releaseRBTree(RBTree *tree);
//向红黑树插入元素
void insertRBTree(RBTree *tree, KeyType key);
// 红黑树的删除元素
void deleterRBTree(RBTree *tree, KeyType key);
//打印元素
void printRBTree(const RBNode *node, int key, int dir);
// 查找元素
RBNode *searchRBNode(const RBTree *tree, KeyType key);

#endif //DATASTRUCT2_RBTREE_H