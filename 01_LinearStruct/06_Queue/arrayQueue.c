#include "arrayQueue.h"
#include <stdio.h>
//(queue->next/front+1)MaxQueueSize,表示next/front向后移,类似于环形
//队头和队尾才是删除和插入位置,maxsizs只是容量,下标不起实际作用
void initArrayQueue(ArrayQueue *queue) {//都在起始位置0
    queue->front=0;
    queue->rear=0;
}

int isEmptyArrayQueue(const ArrayQueue *queue) {//当front和rear相等时队列为空
    if (queue->front==queue->rear) {
        return 1;
    }
    return 0;
}

int isFullArrayQueue(const ArrayQueue *queue) {//空出一个节点不存数据,当队尾向后移与队头重合,则队列已满,此时的位置不存数据
   if ( (queue->rear+1)%MaxQueueSize==queue->front) {
       return 1;
   }
    return 0;
}

void enQueueArrayQueue(ArrayQueue *queue, element_t val) {//rear位置插入
    if (isFullArrayQueue(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->data[queue->rear] = val;//rear开始指向的位置是空的
    queue->rear = (queue->rear+1)%MaxQueueSize;//向后移一位,保证rear始终指向一个空的位置
}

void deQueueArrayQueue(ArrayQueue *queue) {//front位置删除
    if (isEmptyArrayQueue(queue)) {
        printf("Queue is empty\n");
        return;
    }
    queue->front = (queue->front+1)%MaxQueueSize;//向后移一位
}

element_t getFrontArrayQueue(const ArrayQueue *queue) {
    return queue->data[queue->front];
}
