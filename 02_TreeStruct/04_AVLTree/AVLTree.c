#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
static  int maxNum(int a, int b) {
    return a > b ? a : b;//谁大输出谁
}
static int h(const AVLNode *node) {//输出该节点的高度
    if (node==NULL) {
        return 0;
    }
    return node->height;
}

static int getBalance(const AVLNode *node) {
    if (node==NULL) {
        return 0;
    }
    return h(node->left)-h(node->right);//左-右
}
//左旋操作
/* 左旋操作
     x                             y
    / \     ==============>       / \
   lx  y    ==============>      x  ry
      / \                       / \
     ly ry                     lx ly
*/
static AVLNode* leftRotate(AVLNode *x) {
    //调整节点关系
    AVLNode* y= x->right;//创建y节点,用y存x的右子树
    x->right = y->left;//让y的左边移到x的右边
    y->left = x;//再让y的左边指向x===>y成为父节点
    //更新x和y的高度,先更新x节点的高度再更新y节点的高度
    x->height = maxNum(h(x->left), h(x->right))+1;//加1是算上自己
    y->height = maxNum(h(y->left), h(y->right))+1;
    return y;//此时的根节点
}

//右旋操作
/* 右旋操作
     y                               x
    / \                             / \
   x  ry    ==============>        lx  y
  / \                                 / \
 lx rx      ==============>          rx  ry
 */
static AVLNode* rightRotate(AVLNode *y) {
    //调整节点关系
    AVLNode* x = y->left;//创建x节点,用x存y的左子树
    y->left = x->right;//让x的右边移到y的左边
    x->right=y;//再让x的右边指向y===>x成为父节点
    //更新x和y的高度,先更新x节点的高度再更新y节点的高度
    y->height = maxNum(h(y->left), h(y->right))+1;
    x->height = maxNum(h(x->left), h(x->right))+1;
    return x;//此时的根节点
}


AVLTree * createAVLTree() {
    AVLTree *tree=(AVLTree*)malloc(sizeof(AVLTree));
    if (tree==NULL) {
        return NULL;
    }
    tree->root=NULL;
    tree->count=0;
    return tree;
}

static void freeAVLNode(AVLTree *tree, AVLNode *node) {//释放树节点(后序遍历的逻辑)
    if (node==NULL) {
        return;
    }
    freeAVLNode(tree,node->left);
    freeAVLNode(tree,node->right);
    free(node);//释放节点
    tree->count--;
}

void releaseAVLTree(AVLTree *tree) {//释放树结构
    freeAVLNode(tree,tree->root);
    printf("tree have %d node\n",tree->count);
    free(tree);//释放树头结构
}

void visitAVLNode(const AVLNode *node) {
    if (node!=NULL) {
        printf("\t<%d:%d>",node->data,node->height);
    }
}

static AVLNode *createAVLNode(element_t e) {
    AVLNode *node=(AVLNode*)malloc(sizeof(AVLNode));
    if (node==NULL) {
        return NULL;
    }
    node->data=e;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}

/*递归从node节点开始插入元素:插入时就会进行平衡*/
static AVLNode *insertAVLNode(AVLTree *tree,AVLNode *node,element_t e) {
    //1.递归找到要插入的位置
    if (node==NULL) {
        //已经递归到空的位置处了(插入位置),带着新节点原路返回,更新节点高度,判断平衡因子
         AVLNode *newNode=createAVLNode(e);
        if (newNode==NULL) {//申请失败
            return NULL;
        }
        tree->count++;
        return newNode;//插入的终点
    }
    //1.1递的过程
    /*开始的node就是根节点,归完以后就是给根节点的left或right赋值(如果可以插入都是从newNode处退出)*/
     if (e<node->data) {
        node->left=insertAVLNode(tree,node->left,e);//小就向左递归
     }else if (e>node->data) {
         node->right=insertAVLNode(tree,node->right,e);//大就向右递归
     }else {
         return node;//插入的是已经存在的值,将自己返回
     }

    //2.开始进行平衡化的操作(在归的过程中)
    //2.1更新归中每个节点的高度
    node->height=1+maxNum(h(node->left),h(node->right));//计算当前node节点的高度
    //2.2计算当前节点的平衡因子
    int balance=getBalance(node);
    if (balance>1) {//失衡点的左边高度高了
        //判断失衡节点的左边节点L还是R出现新节点
        // node是当前递归层中触发“左子树过高失衡”的那个节点（失衡根节点）
        if (e>node->left->data) {  //更大插在右边,LR--->先调整为LL
            //为什么是只用>失衡点->left:因为LR中的R代表新节点插在了失衡点->left这个点的右子树,此时一定会插入在右子树(见.h函数)
          node->left=leftRotate(node->left);//LR-->LL
        }
       //LL,变成LL后右旋
        return rightRotate(node);
    }
    if (balance<-1) {//失衡点的右边高度高了
        //判断失衡节点的左边节点R还是L出现新节点
        if (e<node->right->data) {//更小插在左边,RL--->先调整为RR,同理e<node->left->data一定就在左子树
            node->right=rightRotate(node->right);
        }
        //RR,变成RR后左旋
        return leftRotate(node);
    }
    return node;
}
/*插入动作完成后（新节点创建并挂接到树中），递归进入 归 的阶段时，会逐节点执行这段高度更新、平衡因子计算、旋转调整的代码 —— 而且不是只执行一次，
 而是从插入位置的父节点开始，向上回溯到根节点的每一层递归，都会执行这段逻辑*/


/*二叉平衡树插入元素e:
 *1.按照二叉搜索树的规则,递归找到插人的位置
 *2.归的流程,更新原路径的节点高度,同时计算平衡因子
 *3.如果发现条件满足进行干预
 */
void insertAVLTree(AVLTree *tree, element_t value) {
     if (tree!=NULL) {
    tree->root=insertAVLNode(tree,tree->root,value);
     }

}

AVLNode *searchAVLTree(const AVLTree *tree, element_t value) {
    AVLNode *current=tree->root;//先用current存根节点
    while (current!=NULL) {
        if (current->data==value) {//找到目标元素
            return current;
        }
        if (value<current->data) {//偏小-->左走
            current=current->left;
        }else {                   //偏大-->右走
            current=current->right;
        }
    }
    return NULL;
}


/*删除的核心逻辑:
 * 1.按照二叉搜索树的规则,递归找到元素value的节点
 * 2.根据度,进行删除,度为2,要找前驱或后继节点
 * 3.原路返回,归的过程中计算高度
 */
static AVLNode *deleteAVLNode(AVLTree *tree, AVLNode *node,element_t e) {
    //找到要删除的节点
    if (node==NULL) {//未找到目标节点,或者在删除后「子树为空」时返回空指针
        return NULL;
    }
    if (e<node->data) {// 目标在左子树，递归删除左子树中的目标节点
        node->left=deleteAVLNode(tree,node->left,e);
    }else if (e>node->data) {// 目标在右子树，递归删除右子树中的目标节点
        node->right=deleteAVLNode(tree,node->right,e);
    }else {
        //找到目标节点node，执行删除操作(判断该节点的度情况)
        AVLNode *tmp;//在删除操作中临时存储、访问或替换目标节点及其相关节点
        if (node->left==NULL||node->right==NULL) {//度为0或1
            if (node->left != NULL) {
                tmp = node->left; // node有左子树 → tmp指向左子节点
            } else {
                tmp = node->right; // node有右子树 → tmp指向右子节点
            }
            if (tmp==NULL) { //度为0(目标节点无子树)--->直接删除node,返回NULL进行归
                tree->count--;
                free(node);
                return NULL;
            }
            //度为1(目标节点有一个子树)-->用孩子节点的值覆盖当前节点(让tmp"取代"node),此时tmp指向的是node的子树
            node->data=tmp->data;//node继承tmp节点的值
            //以下写法可以完整继承 tmp 的所有子树(子树可以为空)
            node->left=tmp->left;//node继承tmp节点的左子树
            node->right=tmp->right;//node继承孩子节点的右子树
            tree->count--;
            free(tmp);
        }


        else {
            //度为2,找前驱节点,更新当前度为2的点的值,删除这个前驱节点
            tmp=node->left;//前驱在当前节点的左子树,让tmp进入左子树
            while (tmp->right!=NULL) {// 找左子树的最右节点（前驱节点，值小于当前节点且最大）
                tmp=tmp->right;
            }//出while后tmp是目标节点前驱
            node->data=tmp->data;//用前驱节点的值覆盖当前节点
            node->left=deleteAVLNode(tree,node->left,tmp->data);//递归删除前驱节点(前驱是当前节点左子树的最右节点,因此它的度只会是1或0,而且1一定是左子树,因此递归后可在前面度为1或0的情况删除)
        }
    }
    //2.已经删除,更新平衡因子,LL LR RR RL状态,由于是删除行为,不能判断当前节点和值进行比较,只能用平衡因子的正负号来决定
    node->height=1+maxNum(h(node->left),h(node->right));//该语句即以下会多次执行,在归的过程中自下而上平衡
    int balance=getBalance(node);//getBalance返回h(node->left) - h(node->right)
    if (balance>1) {//失衡点的左边高度高了LX
         if (getBalance(node->left)<0) {//已经是LX,失衡点的左边多,传入node的左节点,此时if是失衡点左子树的右边多了,LR
             //将R左旋变成LL
             node->left=leftRotate(node->left);//LR
         }
        return rightRotate(node);//LL
    }
    if (balance<-1) {   //失衡点的右边高度高了RX
        if (getBalance(node->right)>0) {//已经是RX,失衡点的右边多,传入node的右节点,此时if是失衡点右子树的左边多了,RL
            //将L左旋变成RR
            node->right=rightRotate(node->right);//RL
        }
        return leftRotate(node);//RR
    }
    return node;//原路返回,是当前这一轮归(单次递归回溯)的结束标志
}
/*删除函数结束:顶层递归（以根节点为起点的最外层递归调用）执行 return node;（或任意return语句-->左旋或右旋），就是整个 deleteAVLNode 函数的结束标志*/
/*
 * 度为0:直接删除
 * 度为1:把有数据的位置进行替换
 */
/*度为2
 * 后继节点:右边的最小值,右边的极左
 * 前驱节点:左边的最大值,左边的极右
 * 替换度为2的点,把删除任务转换为删除后继或前驱(度为0或1)
 */
void deleteAVLTree(AVLTree *tree, element_t value) {
   if (tree!=NULL) {
    tree->root=deleteAVLNode(tree,tree->root,value);
    }
}

int heightAVLTree(const AVLTree *tree) {
    return h(tree->root);
}

/*中序遍历*/
static void inOrderAVLNode(const AVLNode *node) {
    if (node==NULL) {
        return;
    }
    inOrderAVLNode(node->left);
    visitAVLNode(node);
    inOrderAVLNode(node->right);
}

void inOrderAVLTree(const AVLTree *tree) {
 inOrderAVLNode(tree->root);
}
