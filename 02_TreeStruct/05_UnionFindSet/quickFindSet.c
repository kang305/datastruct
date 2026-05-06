#include "quickFindSet.h"
#include<stdio.h>
#include<stdlib.h>
//data 数组和 groupID 数组在设计上是完全平行的，它们的索引 i 始终指向同一个元素的不同属性
QuickFindSet * createQuickFindSet(int capacity) {
    QuickFindSet *setQF=(QuickFindSet *)malloc(sizeof(QuickFindSet));
    if(setQF==NULL) {//申请失败
        return NULL;
    }
    // 分配数据和组ID数组空间
    setQF->data=(int *)malloc(capacity*sizeof(element_t));
    setQF->groupID=(int*)malloc(sizeof(int)*capacity);
    setQF->capacity=capacity;
    setQF->n=0;
    return setQF;
}

void releaseQuickFindSet(QuickFindSet *setQF) {
    if(setQF!=NULL) {
        free(setQF->data);
        free(setQF->groupID);
        setQF->capacity=0;
        setQF->n=0;
        free(setQF);
    }
}

void initQuickFindSet(QuickFindSet *setQF, const element_t *data, int n) {//形参中的data是自己定义的一个数组(在main中)
    if (n > setQF->capacity) {//保证n的值不超过capacity,防止数组越界
        n = setQF->capacity;
    }
    for (int i = 0; i < n; ++i) {
        setQF->data[i] = data[i];       // 复制元素,将data[i]中的数据复制到setQF->data[i]中
        setQF->groupID[i] = i;			// 每个元素初始属于自己的组（组ID = 索引）
    }
    setQF->n = n; // 更新当前元素个数
}

static int findIndex(const QuickFindSet* setQF, element_t e) {//查找元素e在data数组中的索引。
    for (int i = 0; i < setQF->n; ++i) {//只有n个元素,循环n次
        if (setQF->data[i] == e) {//data[i]中的值==目标值
            return i;   //i就是索引,下标 i,它是连接 data 和 groupID 两个数组的桥梁
        }
    }
    return -1;//未找到
}

int isSameQF(const QuickFindSet *setQF, element_t a, element_t b) {
    int indexA = -1, indexB = -1;//先初始化
    //分别寻找a和b的索引
    indexA = findIndex(setQF, a);
    indexB = findIndex(setQF, b);
    if (indexA == -1 || indexB == -1) {//至少有一个未找到
        return 0;
    }
    return setQF->groupID[indexA] == setQF->groupID[indexB];//集团相同则为1不同则为0
}
//i 是寻找 index 的工具，index 是打开 groupID 信息的钥匙。
//data中的第n个元素一定对应groupID中的第n个元素
void unionQF(const QuickFindSet *setQF, element_t a, element_t b) {
    int indexA = -1, indexB = -1;
    //找a和b元素所在的下标
    indexA = findIndex(setQF, a);
    indexB = findIndex(setQF, b);
    if (indexA == -1 || indexB == -1) {//未找到
        return ;
    }
    int groupA = setQF->groupID[indexA];//找到a所归属的集团(就是groupID[indexA])
    int groupB = setQF->groupID[indexB];//找到b所归属的集团(就是groupID[indexB])
    if (groupA == groupB) {
        return;
    }
    // 将groupB的所有成员改为groupA
    for (int i = 0; i < setQF->n; ++i) {
        if (setQF->groupID[i] == groupB) {//找到b元素所在集团的所有元素
            setQF->groupID[i] = groupA;//将B集团的元素改为A集团
        }
    }
}
