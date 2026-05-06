#include "quickUnionSet.h"
#include<stdio.h>
#include<stdlib.h>

QuickUnionSet * createQuickUnionSet(int capacity) {
    QuickUnionSet* setQU = (QuickUnionSet*)malloc(sizeof(QuickUnionSet));
    if(setQU == NULL) {
        return NULL;
    }
    setQU->data = (element_t*)malloc(capacity * sizeof(element_t ));
    setQU->parentID = (int*)malloc(sizeof(int)*capacity);
    setQU->size = (int*)malloc(sizeof(int)*capacity);
    return setQU;
}

void releaseQuickUnionSet(QuickUnionSet *setQU) {
    if(setQU != NULL) {
        free(setQU->data);
        free(setQU->parentID);
        free(setQU->size);
        free(setQU);
    }
}

void initQuickUnionSet(QuickUnionSet *setQU, const element_t *data, int n) {
    for(int i = 0; i < n; i++) {
        setQU->data[i] = data[i];       // 存储元素
        setQU->parentID[i] = i;         // 每个元素的父节点初始化为自身（自己是根节点）
        setQU->size[i] = 1;             // 每个集合大小初始化为 1（只有自身）
    }
    setQU->n = n;                      // 记录当前元素数量
}
static int findIndex(const QuickUnionSet* setQU, element_t e) {
    for (int i = 0; i < setQU->n; ++i) {//下标是0--n-1
        if (setQU->data[i] == e) {//返回目标值的下标索引
            return i;
        }
    }
    return -1;//未找到
}

// 找e元素的根节点索引号，查找效率和树的高度有关
static int findRootIndex(const QuickUnionSet* setQU, element_t e) {
    int index = -1;
    index = findIndex(setQU, e);
    if (index == -1) {
        return -1;
    }
    // 从parentID中不断找父节点，直到某一个点的父节点就是他本身，这个点就是根(根节点的父节点就是自己)
    while (setQU->parentID[index] != index) {
        index = setQU->parentID[index];//让当前的 index 不断地去寻找它所对应节点的父节点的索引，直到找到一个指向自身的节点（即根节点）为止
    }
    return index;// 返回根节点索引
}


//找根节点时,走过的路径都记录起来,当找到根节点时,把刚刚记录的节点,统统把其父节点的关系直接更新到根节点上(让所有子节点都直接指向根节点)-->栈(只用维护一个栈顶指针)
static int findRootIndexWithPathCompress(const QuickUnionSet *setQU, element_t e) {//路径压缩
    int index = -1;
    index = findIndex(setQU, e);  // 先找元素 e 的索引
    if (index == -1) {
        return -1;                //未找到
    }
    // 用链式栈保存查找路径上的所有节点索引
    SetNode *stackTop = NULL;//栈顶指针
    while (setQU->parentID[index] != index) {//不为根节点
        // 当前节点入栈-->头插法
        SetNode *newNode =(SetNode*)malloc(sizeof(SetNode));//创建结构体
        newNode->index = index;//用newNode->index保存当前的index
        newNode->next = stackTop;//将新节点的 next 指针指向当前的栈顶节点(链式栈用头插法)
        stackTop = newNode;//将栈顶指针更新为新插入的节点
        index = setQU->parentID[index];//找index节点的父节点的索引
    }
    //出循环后index就是根节点的索引
    // 根节点找到了，路径压缩，上一步找根的路径的节点都更新其parentID指向根索引（index）
    while (stackTop != NULL) {
        SetNode *temp = stackTop;//用temp存栈顶元素
        setQU->parentID[stackTop->index] = index;    //栈里stack->index是根节点的子节点分别的索引,将他们的父节点都改为根节点
        stackTop = stackTop->next;//栈顶向下走
        free(temp);//把temp释放
    }
    return index;//返回根节点索引
}

int isSameQU(const QuickUnionSet *setQU, element_t a, element_t b) {
    int rootA = findRootIndexWithPathCompress(setQU, a);
    int rootB = findRootIndexWithPathCompress(setQU, b);
    if (rootA == -1 || rootB == -1) {
        return 0;
    }
    return rootA == rootB;//相同返回1,不同返回0
}

void unionQU(const QuickUnionSet *setQU, element_t a, element_t b) {//路径压缩
    int rootA = findRootIndexWithPathCompress(setQU, a);//找a的根节点的索引
    int rootB = findRootIndexWithPathCompress(setQU, b);//找b的根节点的索引
    if (rootA == -1 || rootB == -1) {//至少有一个不存在
        return ;
    }
    if (rootA == rootB) {		// 已经在同一个集合里
        return;
    }
    // 根管理了这个集合，根据根对应的size情况按大小合并：将小集合合并到大集合中（减少树的高度）-->让大集合的根节点变为小集合的父节点(让小集合的父节点索引下标变为大集合的索引)
    if (setQU->size[rootA] < setQU->size[rootB]) {
        setQU->parentID[rootA] = rootB;//小集合根节点指向大集合根节点-->开始parentID[rootA]中存的就是rootA(根节点),将其改为rootB(大集合的根节点),下面同理
        setQU->size[rootB] += setQU->size[rootA];//更新根节点的子节点的数量
    } else {
        setQU->parentID[rootB] = rootA;// 小集合根节点指向大集合根节点
        setQU->size[rootA] += setQU->size[rootB];//更新根节点的子节点的数量
    }
    //原来的所以子节点都存的是根节点,在两个集团合并的时候,只是原先根节点的父节点更新,原先根节点的子节点的父节点还是不变(原先根节点),但该集团所有的根节点都改变了
}
void unionQU2(const QuickUnionSet *setQU, element_t a, element_t b) {//基于rank,元素少的树嫁接到元素多的树上
    int rootA = findRootIndex(setQU, a);
    int rootB = findRootIndex(setQU, b);
    if (rootA == -1 || rootB == -1) {
        return ;
    }
    if (rootA == rootB) {		// 已经在同一个集合里
        return;
    }
    // 根管理了这个集合，根据根对应的size情况，来进行合并,同上
    if (setQU->size[rootA] < setQU->size[rootB]) {
        setQU->parentID[rootA] = rootB;//让a的根变为b的根的子节点
        setQU->size[rootB] += setQU->size[rootA];//更新根节点的子节点的数量
    } else {
        setQU->parentID[rootB] = rootA;
        setQU->size[rootA] += setQU->size[rootB];//更新根节点的子节点的数量
    }
    //只改变原先根节点的父节点的原因:同上
}
