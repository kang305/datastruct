#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
//在堆上产生树头空间,返回这个堆空间的地址
BinaryTree * createBinaryTree() {
 BinaryTree *tree=(BinaryTree *) malloc(sizeof(BinaryTree));
 if (tree == NULL) {
  return NULL;
   }
    tree->root=NULL;
    tree->cnt=0;//此时只是有一个树头结构,没有实际的根节点,cnt==0
 return tree;
}

//释放树,与后序遍历的核心相同
static void destroyTreeNode(BinaryTree *tree, TreeNode *node) {
 if (node!=NULL) {
  destroyTreeNode(tree, node->left);
  destroyTreeNode(tree, node->right);
  free(node);
  tree->cnt--;
 }
}
void releaseBinaryTree(BinaryTree *tree) {
destroyTreeNode(tree, tree->root);
 printf("Binary tree node:%d\n",tree->cnt);
}

//在空树中初始化根节点,当树头不管不是在堆上申请时,都需要初始化
void initBinaryTree(BinaryTree *tree, TreeNode *root) {//root是树的根节点
 if (tree&&tree->root==NULL) {
   tree->root=root;//让根指针指向根节点
   tree->cnt=1;//根节点也算一个节点
    }
}

TreeNode * createTreeNode(element_t data) {//创建树节点并进行初始化
  TreeNode *node=(TreeNode *) malloc(sizeof(TreeNode));
  if (node == NULL) {
   return NULL;
  }
 node->data=data;
 node->left=NULL;
 node->right=NULL;
 return node;
}
//将已经存在的离散的树节点,建立关系
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right) {
 if (parent==NULL||tree==NULL) {//没有父节点和树结构直接退出
  return;
  }
 parent->left=left;
 parent->right=right;
 if (left!=NULL) {
  tree->cnt++;
  }
 if (right!=NULL) {
  tree->cnt++;
 }
}
//用显示树节点里的数据情况,作为处理/访问节点的逻辑
void visitBinaryTree(const TreeNode *node) {
 if (node!=NULL) {
  printf("\t%c",node->data);
 }
}
//广度遍历
/*由于激活了一个根节点,有了左右两个新任务的出现,处理者一次只能处理一个,另外一个可能会丢失,
 *生产者太快,消费者太慢了,中间增加一个缓存区(队列)
 * 缓存区 其他接口是不需要的,缓存区放置在栈上(顺序队列)
 */
//(queue->next/front+1)MaxQueueSize,表示rear/front向后移,类似于环形
//队头和队尾才是删除和插入位置
#define MAX_QUEUE_SIZE 8
void levelOrderBTree(const BinaryTree *tree) {
  TreeNode *queue[MAX_QUEUE_SIZE];
  int front=0;
  int rear=0;

 //1.任务初始化:先让队头入队
 queue[rear]=tree->root;
 rear=(rear+1)%MAX_QUEUE_SIZE;
 //2.循环处理任务,直到任务处理完成(缓存区没任务了):不断出队和入队直到所以树节点用完
 while (rear!=front) {//当队列为空的时候退出
  //2.1从缓存区里取一个任务
  TreeNode *node=queue[front];//临时变量先取front
  front=(front+1)%MAX_QUEUE_SIZE;//从front开始出队
  //2.2访问/处理
  visitBinaryTree(node);//访问此时出队的树节点
  //2.3新的任务送入缓存区
  if (node->left!=NULL) {
   queue[rear]=node->left;
   rear=(rear+1)%MAX_QUEUE_SIZE;
    }
  if (node->right!=NULL) {
   queue[rear]=node->right;
   rear=(rear+1)%MAX_QUEUE_SIZE;
    }
  }
 printf("\n");
}
//深度遍历,一直走直到走不动,返回,处理另外一条路径,递归
/*先序或后序确定根,中序确定根的左右*/
//先序遍历:根节点->左子树->右子树
static void preOrderNode(const TreeNode *node) {
 if (node!=NULL) {
  visitBinaryTree(node);
  preOrderNode(node->left);
  preOrderNode(node->right);
   }
}
void preOrderBTree(const BinaryTree *tree) {
 if (tree!=NULL) {
  preOrderNode(tree->root);
 }
}

//中序遍历:左子树->根节点->右子树
static void inOrderNode(const TreeNode *node) {
 if (node!=NULL) {
  inOrderNode(node->left);
  visitBinaryTree(node);
  inOrderNode(node->right);
 }
}
void inOrderBTree(const BinaryTree *tree) {
 if (tree!=NULL) {
  inOrderNode(tree->root);
 }
}

//后序遍历:右子树->左子树->根节点
static void postOrderNode(const TreeNode *node) {
 if (node!=NULL) {
  postOrderNode(node->left);
  postOrderNode(node->right);
  visitBinaryTree(node);
 }
}
void postOrderBTree(const BinaryTree *tree) {
 if (tree!=NULL) {
  postOrderNode(tree->root);
 }
}
/*__________________________________非递归_________________________________________*/
#define MAX_STACK_SIZE 8
//先序遍历
/*非递归先序遍历基本思路:
 *引入一个栈做任务结构,一旦处理一个任务的时候,先把它的右任务压栈,然后再压入左任务(栈先进后出)
 * 弹栈弹出新任务,每个新任务重复上述操作
 * 根节点 → 左子树 → 右子树
 */
void preOrderBTreeV2(const BinaryTree *tree) {//先序遍历
   TreeNode *stack[MAX_STACK_SIZE];
   int top=-1; //满递增栈

 //1.初始化
stack[++top]=tree->root;//栈顶指针先移动
 //2.循环处理,直到任务没有
     while (top!=-1) {//top!=-1说明栈顶有任务,要取出来
      TreeNode *node=stack[top--];//先取后减
      visitBinaryTree(node);
      //右子节点先入栈，左子节点后入栈(左子节点可以先出栈)
      if (node->right!=NULL) {// 右子树入栈
       stack[++top]=node->right;
      }
      if (node->left!=NULL) {// 左子树入栈
       stack[++top]=node->left;
      }
    }
}

//中序遍历
/*非递归中序遍历基本思路:
 *以根节点开始,整条左边进栈
 * 从栈中弹出节点,开始访问,然后以这个节点的右孩子为新节点
 * 再次按照整条左边进栈,再谈栈
 * 左子树 → 根节点 → 右子树
 */
void inOrderBTreeV2(const BinaryTree *tree) {
TreeNode *stack[MAX_STACK_SIZE];
 int top=-1;   //满递增栈

 TreeNode *current=tree->root;//有新节点
    while (current!=NULL||top!=-1) {//top!=-1说明栈顶有任务,只有两个都是0时才退出
       while (current!=NULL) {//新节点的整条左边入栈,新节点先入栈,处理完后面其他的才能处理新节点(栈先进后出的性质)
        stack[++top]=current;
        current=current->left;
       }
     //左边压完
     current=stack[top--];//弹栈
     visitBinaryTree(current);//没有左边,最后入栈的任务,就是中序的结果
     current=current->right;//以右孩子为新节点,重复上述操作,为空则不会进入第二个while,而是继续弹栈,不为空则进入while,并把所有左子树进栈
   }
}

//后序遍历
/*非递归后序遍历基本思路:需要两个栈,第一个是辅助栈,第二个是最后输出的结果栈
 *1.第一阶段:
 *1.1 第一个栈初始化头节点后,弹出放入第二个栈,这样根节点就最后出了
* 1.2 后序遍历的倒数第二个应该是头结点的右孩子，所以辅助栈<先左后右>(才能让右边先入第二个栈)压入
* 1.3 处理从第一个栈里出来的元素时，先压入第二个栈，根据这个任务，先左后右压入第一个栈
* 1.4 直到第一个栈里没有任务，说明树的节点都处理完成
* 2. 第二个阶段：
* 2.1 按照第二个栈，出栈
* 左子树 → 右子树 → 根节点
 */
void postOrderBTreeV2(const BinaryTree *tree) {
 //用 stack1 模拟递归遍历过程，按 “根→右→左” 的顺序入栈（与后序遍历顺序相反）；
 //将 stack1 弹出的节点依次存入 stack2，最终 stack2 中节点的顺序即为 “左→右→根”；
 TreeNode *stack1[MAX_STACK_SIZE + 14];
 TreeNode *stack2[MAX_STACK_SIZE + 14];
 int top1 = -1;
 int top2 = -1;

 stack1[++top1] = tree->root;
 while (top1 != -1) {//辅助栈内有任务
  TreeNode *node = stack1[top1--];		// 栈1弹栈,用node保存弹栈节点
  stack2[++top2] = node;					       // 把栈1弹栈的节点压入栈2
  //将左子节点先入stack1，右子节点后入stack1-->弹入stack2的节点就是先右后左,stack2弹栈就是先左后右
  if (node->left!=NULL) {					     	// 先左后右压入栈1
   stack1[++top1] = node->left;
  }
  if (node->right!=NULL) {
   stack1[++top1] = node->right;
  }
 }

 while (top2 != -1) {//stack2弹栈
  TreeNode *node = stack2[top2--];
  visitBinaryTree(node);
 }
}