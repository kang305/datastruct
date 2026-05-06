#ifndef DATASTRUCT2_DOUBLELOOPLINK_H
#define DATASTRUCT2_DOUBLELOOPLINK_H
/*节点*/
typedef int element_t;
typedef struct double_node {
    struct double_node *prev;
    struct double_node *next;
    element_t data;
}DulNode;
//带头节点的双向循环链表
typedef struct {//表头
    DulNode header;// 头节点（哨兵节点，不存储实际数据，仅用于连接）
    int num;
}DuLoopLink;
void initDulLoopLink(DuLoopLink *loop_link);//初始化双向循环链表
void insertDulLoopLinkHeader(DuLoopLink *loop_link,element_t val);//头插法
void insertDulLoopLinkTail(DuLoopLink *loop_link,element_t val);//尾插法
void showDulLoopLink(const DuLoopLink *loop_link);//展示
void deleteValueDuLoopLink (DuLoopLink *loop_link,element_t val);//删除元素
void deleteAllDuLoopLink(DuLoopLink *loop_link);//清空链表
#endif //DATASTRUCT2_DOUBLELOOPLINK_H