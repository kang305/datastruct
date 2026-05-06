#include "LinkQueue.h"
#include <stdio.h>
#include <stdlib.h>
LinkQueue *createLinkQueue() {
    LinkQueue * queue = (LinkQueue *)malloc(sizeof(LinkQueue));//申请一个表头
    if (queue == NULL) {//申请失败
        return NULL;
    }
    //初始化表头
    queue->front=queue->rear=NULL;//成功后front和rear指向null
    queue->count=0;
    return queue;
}
void releaseLinkQueue(LinkQueue *queue) {//释放队列
    if (queue == NULL) {//此时队列已经清空
        return;
    }
    QueNode * p=queue->front;//用p记录删除的节点
    while (p!=NULL) {
        QueNode * temp=p;//用temp临时存p
        p=p->next;//p向后更新
        free(temp);//释放temp
        queue->count--;
    }
    printf("LinkQueue have %d node\n",queue->count);
    free(queue);//释放表头
}
int enLinkQueue(LinkQueue *queue, value_t e) {
    QueNode *newNode=(QueNode *)malloc(sizeof(QueNode));//申请新节点
    if (newNode == NULL) {//申请失败
        return -1;
    }
    newNode->data=e;
    newNode->next=NULL;
    if (queue->rear==NULL) {//此时队列中没有节点,rear和front指向newnode
        queue->rear=newNode;
        queue->front=newNode;
    }else {                 //队列中有节点
        queue->rear->next=newNode;//插入时queue->rear指向的是原尾节点,让其next指向新节点
        queue->rear=newNode;//更新rear指针
    }
    queue->count++;
        return 0;
}
int deLinkQueue(LinkQueue *queue, value_t *e) {
    if (queue->front==NULL) {//此时队列已经清空
        return -1;
    }
    QueNode *temp=queue->front;//temp存下此时的队头front
    *e=temp->data;//e存下队头的data
    queue->front=queue->front->next;//queue->front原队头指向下一个
    if (queue->front==NULL) {//此时front已经向后走了,如果front=NULL,此时队列清空,将rear也指向NULL
        queue->rear=NULL;
    }
    free(temp);//释放temp
    queue->count--;
    return 0;
}
