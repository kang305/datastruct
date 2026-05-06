#include "doubleLoopLink.h"
#include <stdlib.h>
#include <stdio.h>
//操作都会避开header,因为他只是在中间串联起整个链表,不存数据
/*定义通用辅助函数,插入,删除*/
static void addDulNode(DulNode* new_node, DulNode* prev, DulNode* next) {//插入,前,后三个节点
    next->prev=new_node; // 后节点（next）的前驱指针，指向新节点
    new_node->next=next; // 新节点的后继指针，指向后节点（next）
    new_node->prev=prev; // 新节点的前驱指针，指向前节点（prev）
    prev->next=new_node; // 前节点（prev）的后继指针，指向新节点
}
static void delDulNode(DulNode* prev, DulNode* next) {//prev和next分别是删除节点的前置与后置节点
    prev->next=next;//删除节点的前节点连接后节点
    next->prev=prev;//删除节点的后节点连接前节点
}

void initDulLoopLink(DuLoopLink *loop_link) {//初始化
    loop_link->num = 0;
    loop_link->header.next=&loop_link->header;
    loop_link->header.prev=&loop_link->header;
}

void insertDulLoopLinkHeader(DuLoopLink *loop_link, element_t val) {//头插法
    DulNode* new_node=(DulNode *)malloc(sizeof(DulNode));//创建节点
    if (new_node==NULL) {
        return;
    }
    new_node->data=val;
    addDulNode(new_node,&loop_link->header,loop_link->header.next);//在链表的 “头节点” 和 “首节点” 之间插入新节点
    ++loop_link->num;
}

void insertDulLoopLinkTail(DuLoopLink *loop_link, element_t val) {
    DulNode* new_node=(DulNode *)malloc(sizeof(DulNode));
    if (new_node==NULL) {
        return;
    }
    new_node->data=val;
    addDulNode(new_node,loop_link->header.prev,&loop_link->header);//第二个形参是最后的节点(头节点的prev指向最后),第三个是头节点
     ++loop_link->num;
}

void showDulLoopLink(const DuLoopLink *loop_link) {
   DulNode* pos=loop_link->header.next;//找首节点(头节点不存数据只是作为中转节点)
   printf("table[%d]\n",loop_link->num);
    while (pos!=&loop_link->header) {//到头节点停下
        printf("%d ",pos->data);
        pos=pos->next;
    }
    printf("\n");
}

void deleteValueDuLoopLink(DuLoopLink *loop_link, element_t val) {
    DulNode* pos=loop_link->header.next;
    while (pos!=&loop_link->header) {
        if (pos->data==val) {
            delDulNode(pos->prev,pos->next);
            free(pos);
            --loop_link->num;
            return;
        }
        pos=pos->next;
    }
    printf("not found\n");
}

void deleteAllDuLoopLink(DuLoopLink *loop_link) {
    DulNode* pos=loop_link->header.next;//直接释放pos,所以pos直接等于第一个元素
    while (pos!=&loop_link->header) {//回到头节点停止
        DulNode* temp=pos->next;//临时存删除节点的下一个,防止丢失
        free(pos);
        pos=temp;//删除pos后,让其指向备份的后一个节点temp
        --loop_link->num;
    }
    loop_link->header.next=&loop_link->header;//让header.next指向自己
    loop_link->header.prev=&loop_link->header;//让header.prev指向自己,以上两步回到初始化
    printf("table num=%d\n",loop_link->num);
}
