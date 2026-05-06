#include "LinkLoop.h"
#include<stdio.h>
#include<stdlib.h>
/*链式表的通用接口*/
static void insertLinkLoop(LinkLoop *link_loop,element_t v,LNode *prev) {//prev为前置节点
    LNode *node=(LNode*)malloc(sizeof(LNode));
    if(node==NULL) {
        return;
    }
    node->data=v;
    node->next=prev->next;//备份思想
    prev->next=node;//插入的前节点指向插入节点
    if (link_loop->rear==prev) {//如果插入位置就是尾部,更新表头的尾指针(尾插法);头插法prev是头节点(header),只有当只存在一个头节点时才更新
        link_loop->rear=node;
    }
    ++link_loop->num;
}

static void delLinkLoop(LinkLoop *link_loop,LNode *prev) {//prev是删除节点的前置节点
    if (prev==NULL||prev->next==&link_loop->header) {//找不到数据,或者前置的后面是头节点
        return;
    }
    LNode *temp=prev->next;
    prev->next=temp->next;
    if (temp==link_loop->rear) {//此时删除的元素在末尾
        link_loop->rear=prev;//rear要指最后一个元素,更新为前一个元素
    }
    free(temp);
    --link_loop->num;
}
/*--------------------------------------------------------------*/
void initLinkLoop(LinkLoop *link_loop) {
    link_loop->header.next=&link_loop->header;
    link_loop->rear=&link_loop->header;
    link_loop->num=0;
}

void insertLinkLoopHeader(LinkLoop *link_loop,element_t v) {
    LNode *prev=link_loop->rear->next;//link_loop->rear->next==header,前置指针此时是头节点(头节点后的节点才是有效节点)
insertLinkLoop(link_loop,v,prev);
}

void insertLinkLoopRear(LinkLoop *link_loop, element_t v) {
    LNode *prev=link_loop->rear;//尾插法的前置节点是尾节点
    insertLinkLoop(link_loop,v,prev);
}

void showLinkLoop(const LinkLoop *link_loop) {
    LNode *p=link_loop->header.next;//第一个元素(首节点)
    printf("link_loop[%d]:",link_loop->num);//个数
while (p!=&link_loop->header) {//返回头节点时结束
    printf("%d ",p->data);
    p=p->next;//向后推
   }
    printf("\n");
}

int deleteLinkLoop(LinkLoop *link_loop, element_t v) {
    LNode *prev=&link_loop->header;//prev是删除节点的前置节点
    while (prev->next!=&link_loop->header) {//从头节点到最后循环
        if (prev->next->data==v) {//找到删除节点
            delLinkLoop(link_loop,prev);
            return 1;//删除成功
        }
        prev=prev->next;
    }
    return 0;
}

void deleteAllLinkLoop(LinkLoop *link_loop) {
    LNode *prev=&link_loop->header;//头节点为删除前置节点
    while (prev->next!=&link_loop->header) {//在指回头节点前循环
        delLinkLoop(link_loop,prev);
    }
    link_loop->rear=&link_loop->header;//重复了,while内完成了,但这样更清晰
    printf("link_loop num=%d\n",link_loop->num);
}
