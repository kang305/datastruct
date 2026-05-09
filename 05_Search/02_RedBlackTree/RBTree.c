#include<stdio.h>
#include<stdlib.h>
#include "RBTree.h"

//左旋
/* 将x进行左旋，将左、右、父节点进行更新
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
*/
static void leftRotate(RBTree* tree,RBNode* x) {
    RBNode* y=x->right;
    x->right=y->left;
    if(y->left) {//防止为空
        y->left->parent=x;//将原先ly的父节点更新为x
    }
    y->parent=x->parent;//更新y的父节点
    if(x->parent) {//x不为根节点
        //看x在祖父节点的左边还是右边，将y继承过去
        if (x->parent->left==x) {
            x->parent->left=y;
        }else {
            x->parent->right=y;
        }
    }else {//x为根节点
        tree->root=y;
    }
    y->left=x;
    x->parent=y;
}

//右旋
/* 将y进行左旋，将左、右、父节点进行更新
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \
 *        x   ry                           lx   y
 *       / \                                   / \
 *      lx  rx                                rx  ry
 * */
static void rightRotate(RBTree* tree, RBNode* y) {
    RBNode* x=y->left;
    y->left=x->right;
    if(x->right) {//检查x->right是否为空
        x->right->parent=y;
    }
    x->parent=y->parent;
    if(y->parent) {
        if (y->parent->left==y) {
            y->parent->left=x;
        }else {
            y->parent->right=x;
        }
    }else {//y为根节点
        tree->root=x;
    }
    x->right=y;
    y->parent=x;
}
/* 插入后修复红黑树性质
 * 1. 如果父节点是黑色，不用调整
 * 2. 如果父节点是红色，出现“红红”冲突，需要调整
 *   2.1 叔叔节点是红色 → 重新着色（祖父变红，父和叔变黑），并将祖父作为新节点继续向上检查
 *   2.2 叔叔节点是黑色（或为NULL）
 *       LL型：当前节点是父的左孩子，父是祖父的左孩子 → 右旋祖父，祖父变红，父变黑
 *       RR型：当前节点是父的右孩子，父是祖父的右孩子 → 左旋祖父，祖父变红，父变黑
 *       LR型：当前节点是父的右孩子，父是祖父的左孩子 → 左旋父，然后交换当前节点与父指针，转为LL处理
 *       RL型：当前节点是父的左孩子，父是祖父的右孩子 → 右旋父，然后交换当前节点与父指针，转为RR处理
 */
static void insertFixUp(RBTree *tree, RBNode *node) {//调整函数,node是当前要插入的节点
    RBNode *parent,*grandparent;
    RBNode *uncle;
    RBNode *tmp;//用于交换
    parent=node->parent;
    //如果父节点是红色，违反了红红
    while (parent&&parent->color==RED) {
        //找到祖父节点，根据祖父节点和父节点的关系，确定叔叔节点(祖父节点一定存在->父节点为red)
        grandparent=parent->parent;
        if (parent==grandparent->left) {//叔叔节点在父节点的另外一边
            uncle=grandparent->right;
        }else {
            uncle=grandparent->left;
        }
        if (uncle&&uncle->color==RED) {//2.1叔叔节点存在且为RED
            uncle->color=BLACK;
            parent->color=BLACK;
            grandparent->color=RED;
            node=grandparent;          //将祖父作为新的当前节点
            parent=node->parent;       //更新父指针，继续向上检查
            continue;
        }
        //2.2叔叔节点为BLACK或者不存在
        if (grandparent->left==parent) {  // L
            if (parent->right==node) {    // LR
                // LR型：当前节点是父的右孩子，父是祖父的左孩子 → 左旋父，然后交换当前节点与父指针，转为LL处理
                leftRotate(tree,parent);
                tmp=parent;
                parent=node;
                node=tmp;
            }
            //LL
            //LL型：当前节点是父的左孩子，父是祖父的左孩子 → 右旋祖父，祖父变红，父变黑
            rightRotate(tree,grandparent);
            grandparent->color=RED;
            parent->color=BLACK;
        }
        else {    // R
            if (parent->left==node) {  //RL
                // RL型：当前节点是父的左孩子，父是祖父的右孩子 → 右旋父，然后交换当前节点与父指针，转为RR处理
                rightRotate(tree,parent);
                tmp=parent;
                parent=node;
                node=tmp;
            }
            // RR
            //RR型：当前节点是父的右孩子，父是祖父的右孩子 → 左旋祖父，祖父变红，父变黑
            leftRotate(tree,grandparent);
            grandparent->color=RED;
            parent->color=BLACK;
        }
    }
    //循环结束后，确保根节点为黑色
    tree->root->color=BLACK;
}

static RBNode* createRBNode(KeyType key) {//创建节点
    RBNode* node=(RBNode*)malloc(sizeof(RBNode));
    node->key=key;
    node->color=RED;
    node->left=node->right=node->parent=NULL;
    return node;
}


RBTree * createRBTree() {//创建树头结构
    RBTree *tree=malloc(sizeof(RBTree));
    tree->count=0;
    tree->root=NULL;
    return tree;
}

void insertRBTree(RBTree *tree, KeyType key) {
    //1.先创建一个红色节点
    RBNode *node=createRBNode(key);//
    //2.根据二叉搜索树的规则找到待插入的节点
    RBNode *cur=tree->root;
    RBNode *prev=NULL;
    while(cur) {
        prev=cur;
        if (key<cur->key) {
            cur=cur->left;
        }else if (key>cur->key) {
            cur=cur->right;
        }else {
            printf("Key %d have exist!\n", key);
            free(node);
            return;
        }
    }
    //3.在对应位置上插入
    node->parent=prev;
    if(prev) {    //树非空，插入在叶子节点下面
        if (key<prev->key) {//小的插在左边
            prev->left=node;
        }else {//大的值插在右边
            prev->right=node;
        }
    }else {   //如果为根节点，prev=NULL,直接将节点插入根节点下面
        tree->root=node;
    }
    //4.修正红黑树 判断是否出现红红
    insertFixUp(tree,node);
}

//node: 当前节点 key: 父节点的键值，dir: 方向（0表示根，-1左孩子，1右孩子）
void printRBTree(const RBNode *node, int key, int dir) {
    if (node) {
        if (dir == 0) {
            printf("%2d[B] is root\n", node->key);
        } else {
            printf("%2d[%c] is %2d's %s\n", node->key,
                    node->color == RED ? 'R' : 'B', key,
                    (dir == 1) ? "right child" : "left child");
        }
        //递归打印
        printRBTree(node->left, node->key, -1);
        printRBTree(node->right, node->key, 1);
    }
}

RBNode *searchRBNode(const RBTree *tree, KeyType key) {
    RBNode *node=tree->root;
    while(node) {
        if (key<node->key) {
            node=node->left;
        }else if (key>node->key) {
            node=node->right;
        }else {
            return node;
        }
    }

    return NULL;
}
/*从红黑树中删除一个节点*/
static void deleteRBNode(RBTree* tree, RBNode *node) {
    RBNode *y;//真正要删除的节点地址
    RBNode *x;//替换节点

    if (node->left==NULL||node->right==NULL) {//有一个孩子或者没有孩子
        y=node;
    }else { //有左右子树，寻找后继节点(删除节点右子树的最左边)
        y=node->right;
        while (y->left!=NULL) {//退出循环当前的y就是要删除的节点
            y=y->left;
        }
    }
    //真正删除的节点找到了，开始寻找替换节点
    if (y->left!=NULL) {
        x=y->left;
    }else {
        x=y->right;
    }
    //开始更新替换节点和y点父节点的关系

}

void deleterRBTree(RBTree *tree, KeyType key) {

}

RBNode *searchRBNode(const RBTree *tree, KeyType key) {
    RBNode *node=tree->root;
    while(node) {
        if (key<node->key) {
            node=node->left;
        }else if (key>node->key) {
            node=node->right;
        }else {
            return node;
        }
    }

    return NULL;
}