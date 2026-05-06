
#ifndef DATASTRUCT2_ARRAYQUEUE_H
#define DATASTRUCT2_ARRAYQUEUE_H
#define MaxQueueSize 5
typedef int element_t;
/*循环队列*/
typedef struct{
    element_t data[MaxQueueSize];//对头和对尾才是删除和插入位置,maxsizs只是容量,下标不起实际作用
    int front;
    int rear;
}ArrayQueue;

void initArrayQueue(ArrayQueue *queue);//初始化队列
int isEmptyArrayQueue(const ArrayQueue *queue);//判断队列是否为空
int isFullArrayQueue(const ArrayQueue *queue);//判断队列是否已满
void enQueueArrayQueue(ArrayQueue *queue, element_t val);//插入
void deQueueArrayQueue(ArrayQueue *queue);//删除
element_t getFrontArrayQueue(const ArrayQueue *queue);//获取队头元素
#endif //DATASTRUCT2_ARRAYQUEUE_H