#ifndef DATASTRUCT2_LINKQUEUE_H
#define DATASTRUCT2_LINKQUEUE_H
typedef int value_t;
/*链式队列*/
typedef struct que_node{//节点结构
    value_t data;
    struct que_node *next;
}QueNode;
typedef struct {//表头就是用来找节点删除插入
    QueNode *front;
    QueNode *rear;
    int count;
}LinkQueue;
//采用堆上申请链式队列的头
LinkQueue *createLinkQueue();//申请+初始化表头
void releaseLinkQueue(LinkQueue *queue);//不仅释放链式头,还释放链式队列的所有节点

int enLinkQueue(LinkQueue *queue, value_t e);//插入
int deLinkQueue(LinkQueue *queue, value_t *e);//删除
#endif //DATASTRUCT2_LINKQUEUE_H