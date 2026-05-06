#include <stdio.h>
#include"arrayQueue.h"
#include "LinkQueue.h"
/*从front删除,从rear插入*/
void test1() {
    ArrayQueue queue;
    initArrayQueue(&queue);
    for (int i=0;i<MaxQueueSize;i++) {
        enQueueArrayQueue(&queue, i+10);
    }
    enQueueArrayQueue(&queue, 400);
    while (!isEmptyArrayQueue(&queue)) {
        printf("%d  \n", getFrontArrayQueue(&queue));
        deQueueArrayQueue(&queue);
    }
    deQueueArrayQueue(&queue);
}

void test2() {
    LinkQueue *q=createLinkQueue();
    for (int i=1;i<5;i++) {
        enLinkQueue(q, i*10);
    }
    value_t e;
   deLinkQueue(q, &e);
    printf("delete element=%d  \n", e);
    deLinkQueue(q, &e);
    printf("delete element=%d  \n", e);
    enLinkQueue(q, 50);
    enLinkQueue(q, 60);
    while (deLinkQueue(q, &e)==0) {
        printf("element=%d \n", e);
    }
    deLinkQueue(q, &e);
    releaseLinkQueue(q);
}
int main() {
   test1();
   test2();
}

/**/