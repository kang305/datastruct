#include "threadedBTree.h"
#include<stdio.h>
#include<stdlib.h>
/*中序线索化*/
ThreadedBTree *createThreadedBTree() {//创建树结构(无节点)
    ThreadedBTree* tree=(ThreadedBTree*)malloc(sizeof(ThreadedBTree));
    if (tree!=NULL) {
        tree->root=NULL;
        tree->count=0;
    }
    return tree;
}
static void freeTreeNode(ThreadedBTree *tree, TreeNode *node) {//只走实线子树(tag=0),后序遍历,把节点释放
    if (node) {
        if (node->l_tag == 0) {
            freeTreeNode(tree, node->left);
        }
        if (node->r_tag == 0) {
            freeTreeNode(tree, node->right);
        }
        free(node);
        tree->count--;
    }
}

void releaseThreadedBTree(ThreadedBTree *tree) {
    if (tree) {
        freeTreeNode(tree, tree->root);
        printf("tree have lost %d node\n", tree->count);
        free(tree);//释放树头
    }
}

void initThreadedBTree(ThreadedBTree *tree, TreeNode *root) {//初始化线索树
    if (tree&&tree->root==NULL) {//树头存在且根节点不存在
        tree->root=root;//树头指向根节点
        tree->count=1;//根节点计入节点数中
    }
}

TreeNode* createTreeNode(element_t data) {//创建节点结构
    TreeNode* node=(TreeNode*)malloc(sizeof(TreeNode));//申请节点
    if (node) {//对节点进行初始化
        node->data=data;
        node->left=NULL;
        node->l_tag=0;
        node->right=NULL;
        node->r_tag=0;
    }
    return node;
}

void visitTreeNode(const TreeNode *node) {//访问节点
    if (node) {
        printf("%c\t",node->data);
    }
}
//根节点，父节点，左子节点，右子节点
void insertTheadedBTree(ThreadedBTree* tree,TreeNode *parent,TreeNode* left,TreeNode* right) {
    if (tree&&parent) {
        parent->left=left;
        parent->right=right;
        tree->count+=(left?1:0)+(right?1:0);//如果left存在返回一,否则返回0,right同理(避免2个if)
    }
}

/*prev和cur(node)指针法*/
//prev 始终是 “刚刚处理完的节点”(上一个访问的节点)，node是 “正在处理的节点”。
//在原始树中构建线索(构建虚线)
//前驱和后继节点都是基于当前节点
static TreeNode *prev=NULL;//记录当前节点在中序遍历中的 “前驱节点”（始终指向刚刚处理完的节点）
static void inTheading(TreeNode* node) {//将二叉树中原本为空的左/右指针（称为 “空链域”）利用起来，指向该节点在中序遍历中的前驱或后继节点
    if (node==NULL) {//递归退出的地方
        return;
    }
    /*按照中序遍历的思路*/
    //递归左子树
    inTheading(node->left);
    //处理当前节点
    if (node->left==NULL) {//当前节点左子树为空
        node->l_tag=1;//将其的左指针设为线索
        node->left=prev;//指向前驱,让node->left指向上一个访问的节点
    }
    //如果前驱存在，且前驱的右指针为空-->将前驱的右指针设为线索
    if (prev!=NULL&&prev->right==NULL) {
        prev->r_tag=1;
        prev->right=node;//前驱的右指针指向当前节点(后继),此时还未找到下一个所以只能给当前一个赋值
    }
    prev=node;//更新前驱节点prev但当前节点node会在prev的下一步(让prev为它的后继节点)
    //递归右子树
    inTheading(node->right);//当前节点的后继节点就在右子树中
}
//构建中序线索（把空指针改成前驱or后继线索）
void inOrderTheading(ThreadedBTree *tree) {//构建虚线
   if (tree&&tree->root) {//树和根节点都存在
       prev=NULL;//初始化prev
       inTheading(tree->root);//会处理完所以节点,此时prev会指向最后的节点
       if (prev!=NULL) {//中序遍历的最后一个节点的右指针必然为空，需手动标记为线索（r_tag=1)
           prev->right=NULL;// 最后一个节点没有后继需要手动设置为空
           prev->r_tag=1;
       }
   }
}
//在已经线索化好的二叉树中,进行中序遍历(非递归)
void inOrderTheadedTree(ThreadedBTree *tree) {
    if (tree&&tree->root) {//树和根节点都存在
        TreeNode *node=tree->root;//临时指针
        //找中序遍历得第一个节点(最左的节点)
        while (node->l_tag==0) {//0代表此时指针用实线指向(子树),不具有线索能力,最左的节点的l_tag=1且指向NULL
            node=node->left;//一直向左,让node指向最左的节点(即中序遍历的第一个)
        }
        //此时node就是中序遍历第一个节点
        //线性遍历方式
        while (node) {
            visitTreeNode(node);
            //如果有标志为1,说明右指针是后继节点,用虚线指向
            //找后继节点(r_tag=1)
            if (node->r_tag==1) {//右指针是线索（r_tag=1）→ 直接指向后继节点
                node=node->right;//node更新为后继节点
            }
            //右指针是正常子树（r_tag=0）→ 找当前节点的后继节点(右子树的最左节点,即下一个要访问的节点）
            else {
                //不是线索化的节点,找到一个可以作为访问的node节点
                node=node->right;//进入右子树(右子树的最左节点就是当前节点的后继)-->左子树->根节点->右子树->右子树最左节点
                while (node&&node->l_tag==0) {//找右子树的最左侧节点,如果l_tag=1则node的右子树已经是最左,l_tag=0则代表有左子树(可以继续向左)
                    node=node->left;
                }
            }
        }
    }
}
/*
 *中序遍历的推进方向是 “从前往后”，核心是找每个节点的后继，而 r_tag 直接关联后继信息，因此是遍历的关键。
 *l_tag 关联的是前驱，在正向遍历中不需要用到，仅在初始化找第一个节点时短暂使用。
*/