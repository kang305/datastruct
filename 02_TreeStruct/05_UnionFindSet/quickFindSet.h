#ifndef DATASTRUCT2_QUICKFINDSET_H
#define DATASTRUCT2_QUICKFINDSET_H
#include "common.h"
/*并查集:存相同的集团*/
typedef struct {
    element_t* data; //存放数据的,采用顺序存储,自带了下标索引,作为关系数组里的索引值
    int *groupID;    //groupID[i]的下标,表示第i个元素所归属的集团编号,groupID[i]表示data[i]所在的组ID(一一对应)。
    int n;           //集团中元素的个数
    int capacity;    //集合的容量,data和groupID数组的最大长度。
}QuickFindSet;
//data[i]中的i对应了index
//data 数组和 groupID 数组在设计上是完全平行的，它们的索引 i 始终指向同一个元素的不同属性
QuickFindSet *createQuickFindSet(int capacity);//创建并查集的结构
void releaseQuickFindSet(QuickFindSet *setQF);

//初始化并查集,填写元素的值和构建初始化关系
void initQuickFindSet(QuickFindSet *set,const element_t *data,int n);
//查找:在并查集中,判断两个元素是不是同一个集团
int isSameQF(const QuickFindSet *set,element_t a,element_t b);
//合并:在并查集中,合并两个元素
void unionQF(const QuickFindSet *set,element_t a,element_t b);
#endif //DATASTRUCT2_QUICKFINDSET_H