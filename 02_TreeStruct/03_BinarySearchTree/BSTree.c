#include "BSTree.h"
#include<stdio.h>
#include<stdlib.h>
BSTree* createBSTree() {//创建树结构
BSTree* tree = (BSTree*)malloc(sizeof(BSTree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    tree->count=0;
    return tree;
}
/*_________________________________________________________________________*/
static void FreeNode(BSTree *tree, BSNode* node) {//释放节点-->后序遍历的逻辑
    if (node == NULL) {//递归退出
      return;
    }
    FreeNode(tree, node->left);
    FreeNode(tree, node->right);
    free(node);
    tree->count--;
}

void releaseBSTree(BSTree *tree) {
    if (tree!=NULL) {
        FreeNode(tree, tree->root);//释放节点
        printf("tree count:%d\n",tree->count);
        free(tree);//释放树结构
    }
}
/*_______________________________________________________________________________*/

/*___________________按照二叉搜索树的规则插入数据（递归方式）____________________________*/
//插入规则:左子树值小于根，右子树值大于根
static BSNode *createBSNode(element_t e) {//通过该接口创建节点
    BSNode *node = (BSNode*)malloc(sizeof(BSNode));
    if (node == NULL) {//申请失败
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->data=e;
    return node;
}

static BSNode *insertBSNode(BSTree* tree, BSNode* node,element_t e) {//不会存在相等,node是当前递归处理的子树的根节点
    // 1. 终止条件：当前子树为空（找到了插入位置）
    if (node==NULL) {
        tree->count++;
        return createBSNode(e);//返回创建插入的节点,能够插入时从这退出
    }
    //小的放左边,大的放右边
    //2. 若e小于当前节点值：递归插入到左子树
    if (e<node->data) {
        node->left=insertBSNode(tree, node->left, e);//左边进的返回给左边
    }
    //3. 若e大于当前节点值：递归插入到右子树
    else if (e>node->data) {
        node->right=insertBSNode(tree, node->right, e);//右边进的返回给右边
    }
    // 4. 若e等于当前节点值：不插入（BST不允许重复元素），直接返回当前节点
    return node;//将当前子树的根节点(下面还有已经链接好的这个根节点的子树)指针返回给上层递归调用,不能插入时从这退出
}

void insertBSTreeV1(BSTree *tree, element_t e) {
    if (tree==NULL) {
        return;
    }
    // （初始从树的根节点tree->root开始插入，返回值是插入后新的根节点）
   tree->root= insertBSNode(tree, tree->root,e);
}

/*___________________________________________________________________________________*/


/*____________________按照二叉搜索树的规则插入数据（非递归方式）_____________________________*/
void insertBSTreeV2(BSTree *tree, element_t e) {
    if (tree==NULL) {
        return;
    }
    //pre与cur双指针
    BSNode *pre=NULL;
    BSNode *cur=tree->root;
    while (cur!=NULL) {
        pre=cur;//保存cur前一步的路径
        if (e<cur->data) {//插入值更小,cur向左走
            cur=cur->left;
        }else if (e>cur->data) {//插入值更大,cur向右走
            cur=cur->right;
        }else {//相等直接返回
            return;
        }
    }//出循环pre就位于插入位置的父节点
    BSNode *newNode = createBSNode(e);//创建新节点
    if (pre==NULL) {//树没有节点
        tree->root=newNode;
    }else if (e<pre->data) {
        pre->left=newNode;
    }else{
        pre->right=newNode;
    }
    tree->count++;
}
/*___________________________________________________________________________________*/
BSNode * searchBSTree(const BSTree *tree, element_t e) {
    if (tree==NULL) {//不存在树结构直接退出
        return NULL;
    }
    BSNode *current=tree->root;//保存根节点
    while (current!=NULL) {
        if (current->data==e) {//找到该节点,直接返回
            return current;
        }
        if (e<current->data) {
            current=current->left;//值更小以当前节点往左走
        }else{
            current=current->right;//值更大以当前节点往右走
        }
    }
    return NULL;//没找到
}
/*_______________________按照二叉搜索树的规则删除数据（递归方式）______________________________*/
static BSNode *miniValueBSNode(BSNode *node) {//找极左
    while (node!=NULL&&node->left!=NULL) {
        node=node->left;
    }
    return node;
}

static BSNode *deleteBSNode(BSTree *tree,BSNode *node,element_t e) {//
    if (node==NULL) {//结束条件
        return NULL;
    }
    //找要删除的节点
    if (e<node->data) {
        node->left=deleteBSNode(tree, node->left, e);
    }else if (e>node->data) {
        node->right=deleteBSNode(tree, node->right, e);
    }
    else {    //找到e值所在的节点
        BSNode *temp;//引入辅助指针备份,完成删除操作
        if (node->left==NULL) {//度为1或0
            temp=node->right;
            free(node);
            tree->count--;
            return temp;
        }
        if (node->right==NULL) {//度为1或0
            temp=node->left;
            free(node);
            tree->count--;
            return temp;
        }
        //此时说明待删除的节点,有左右子树(度为2)
        temp=miniValueBSNode(node->right);//右子树找极左值,node->right进入右子树
        node->data=temp->data;//让删除节点的数据变为极左,此时树结构未变,但是目标删除节点的值已经被其右子树极左覆盖(极左的右子树都更大)
        node->right=deleteBSNode(tree, node->right, temp->data);//从右进入的从右边返回,删除右子树的极左(度只能为1或0)
    }
    return node;
}

void deleteBSTreeV1(BSTree *tree, element_t e) {
    if (tree==NULL) {
        return;
    }
    tree->root=deleteBSNode(tree,tree->root,e);//从根节点进入,返回给根节点
}
/*__________________________________________________________________________________________*/

/*_________________________按照二叉搜索树的规则删除数据（非递归方式）_____________________________*/
void deleteBSTreeV2(BSTree *tree, element_t e) {
    if (tree==NULL) {
    return;
    }
    BSNode *pre=NULL;
    BSNode *cur=tree->root;
    //1.找到要删除的节点cur,以及它的父节点pre
    while (cur!=NULL&&e!=cur->data) {//要么cur==NULL退出,要么找到数据退出
        pre=cur;//保存cur前一步的路径
        if (e<cur->data) {
            cur=cur->left;
        }else {
            cur=cur->right;
        }
    }
    if (cur==NULL) {//未找到待删除节点
        printf("no find\n");
        return;
    }

    //开始删除节点cur
    if (cur->left==NULL||cur->right==NULL) {//度为0或1的效果
        BSNode *newCur;//存删除节点后面的一串节点
        if (cur->left) {//说明cur->right==NULL(左子树不为空),用newCur存cur->left
            newCur=cur->left;
        } else {//说明cur->left==NULL(右子树不为空),用newCur存cur->right
            newCur=cur->right;
        }
        if (pre==NULL) {//此时树没有节点
            tree->root = newCur;
        } else if (pre->left == cur) {//删除节点在父节点的左边,把newCur给pre->left
            pre->left = newCur;
        }
        else {                        //删除节点在父节点的右边,把newCur给pre->right
            pre->right = newCur;
        }

        free(cur);
        tree->count--;
    }
    else {//度为2的效果
        /*进入右子树,找极左值*/
        //cur指向需要"删除"的节点
        BSNode *tmpPre = cur;//tmpPre是真正删除节点的父节点
        BSNode *tmpCur = cur->right;//进入右子树
        // 找后继节点，以及后继节点的父节点
        while (tmpCur->left!=NULL) {//找极左值
            tmpPre = tmpCur;
            tmpCur = tmpCur->left;
        }
        //出循环后,tmpCur就是要替换的值(极左),tmpPre是tmpCur的父节点
        cur->data = tmpCur->data;//将cur的值替换,实际删除是tmpCur(目标删除节点的右子树的极左)
        if (tmpPre->left == tmpCur) {//此时进入右子树非极左
            tmpPre->left = tmpCur->right;//此时tmpCur肯定没有左子树点,因为tmpCur是极左,所以将tmpCur->right给tmpPre
        } else {
            tmpPre->right = tmpCur->right;//此时这个刚进右子树就是极左(自然无左子树),把极左的右子树给tmpPre->right
        }
        free(tmpCur);
        tree->count--;
    }
}



/*___________________________________________________________________________________*/
void visitBSNode(const BSNode *node) {
    if (node) {
        printf("%d\t",node->data);
    }
}
/*_______________________________________________________*/
static int heightBSNode(const BSNode *node) {//node是当前节点
    if (node==NULL) {//前节点为 NULL（空树或空子树），其高度为 0。
        return 0;
    }
    int leftHeight= heightBSNode(node->left);//计算当前节点左子树的高度，结果存入 leftHeight
    int rightHeight= heightBSNode(node->right);//计算当前节点右子树的高度，结果存入 rightHeight
    return(leftHeight>rightHeight)?leftHeight+1:rightHeight+1;//+1是代表当前节点（即递归中的 “根节点”）本身。
}

int heightBSTree(const BSTree *tree) {
    if (tree==NULL) {
        return 0;
    }
    return heightBSNode(tree->root);//传入根节点
}
/*_______________________________________________________*/

/*_______________________________________________________*/
/*先递归遍历当前节点的左子树；
  遍历完左子树后，访问当前节点；
  最后递归遍历当前节点的右子树。
左 < 根 < 右” 的 BST 定义 与 “左→根→右” 的中序遍历顺序契合
所以BST 的中序遍历之所以是升序
*/
static void inOrderBSNode(const BSNode* node) {//中序遍历
    if (node==NULL) {
        return;
    }
    inOrderBSNode(node->left);
    visitBSNode(node);
    inOrderBSNode(node->right);
}

void inOrderBSTree(const BSTree *tree) {
    if (tree==NULL) {
        return;
    }
    inOrderBSNode(tree->root);//传入根节点
    printf("\n");
}
/*_______________________________________________________*/


/*_______________________________________________________*/
static void preOrderBSNode(const BSNode* node) {//前序遍历
    if (node==NULL) {
        return;
    }
    visitBSNode(node);
    preOrderBSNode(node->left);
    preOrderBSNode(node->right);
}

void preOrderBSTree(const BSTree *tree) {
    if (tree==NULL) {
        return;
    }
    preOrderBSNode(tree->root);//传入根节点
    printf("\n");
}
static void PostOrderBSNode(const BSNode* node) {//后序遍历
    if (node==NULL) {
        return;
    }
    visitBSNode(node);
    PostOrderBSNode(node->left);
   PostOrderBSNode(node->right);
}

void PostOrderBSTree(const BSTree *tree) {
    if (tree==NULL) {
        return;
    }
    PostOrderBSNode(tree->root);//传入根节点
    printf("\n");
}