#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"
/*链式表的通用接口*/
static int insertNode(LNode *prev,element_t v) {//插入节点通用接口
    LNode *node = (LNode*)malloc(sizeof(LNode));
    if (node == NULL) {//申请失败
        return 0;
    }
    node->data = v;
    node->next=prev->next;//node先备份了prev的后一个节点,prev再指向node
    prev->next=node;
    return 1;
}

static void showNode(const LNode *start) {//展示通用接口
    while (start!=NULL) {
        printf("%d ",start->data);//有多少节点
        start=start->next;//start找下一个节点直到尾节点指向NULL
    }
    printf("\n");
}

static void deleteNode(LNode *prev) {//prev是删除节点的前置节点,所以temp=prev->next
    LNode *temp=prev->next;
    prev->next=temp->next;
    free(temp);
}
/*_________________________________________________________________________*/
void insertHeadertable(LinkTable *table, element_t v) {
    LNode *prev=&table->header;//给头节点的header赋值
   if (insertNode(prev,v)) {
       ++table->num;
    }
}

void insertTailtable(LinkTable *table, element_t v) {
    LNode *prev=&table->header;
   while (prev->next!=NULL) {//找尾节点
       prev=prev->next;
   }
    if (insertNode(prev,v)) {
        ++table->num;
    }
}

void insertPostable(LinkTable *table, int pos, element_t v) {//指定pos位置插入
    if (pos<0||pos>table->num) {
        return;
    }
    LNode *prev=&table->header;
    for (int i=0;i<=pos-1;i++) {//找到pos-1的位置,让prev向后指
        prev=prev->next;
    }
    if (insertNode(prev,v)) {
        ++table->num;
    }
}

void deleteValuetable(LinkTable *table, element_t v) {
    LNode *prev=&table->header;//prev是删除节点的前置节点
    while (prev!=NULL&&prev->next!=NULL) {
        if (prev->next->data==v) {//找到元素v的前置节点
            break;
        }
        prev=prev->next;//移向元素v所在的节点

    }
    if (prev!=NULL&&prev->next!=NULL) {//上面的while有62和64两个出口,如果62为0,69也为0,不进入if;否则从64退出,69为1,进入if
        deleteNode(prev);
        --table->num;
        return;
    }
    if (prev->next==NULL&&prev->data!=v) {
        printf("delete fail\n");
        return ;
    }
}

void deleteAllLinkTable(LinkTable *table) {
    //以头节点为固定节点,作为删除节点的前置节点,一直删除后面的节点,直到头节点的next为NULL
    LNode *prev=&table->header;//prev是删除节点的前置节点
    while (prev->next!=NULL) {
        deleteNode(prev);
        --table->num;
    }
    printf("table num=%d\n",table->num);
}

void showLinkTable(const LinkTable *table) {
    printf("table[%d]\n",table->num);
    LNode *start=table->header.next;//start初始指向头节点的下一个
    showNode(start);
}

/*____________________________________________________________________*/
/*1.在栈上申请dummy节点  2.dummy.next=传入的首元节点  3.*prev=&dummy  4.按照前置节点的逻辑操作  5.dummy.next赋值更新或者返回*/
/*核心是创建出一个临时前置节点
LNode dummy;
dummy.next=list->prt_head;
记得更新list->prt_head
list->prt_head=dummy.next;//更新
*/
void insertHeaderList(LinkList *list, element_t v) {
    LNode dummy;//临时前置节点
    dummy.next = list->prt_head;//prt_head只是一个指针存地址存的是第一个节点的地址,构建一个dummy前置节点;
    LNode *prev=&dummy;//让prev扮演前置节点
    if (insertNode(prev,v)) {
        list->prt_head=dummy.next;//将dummy.next的值给prt_head,释放dummy,更新了prt_head
        ++list->num;
     }
}

void insertTailList(LinkList *list, element_t v) {
    LNode dummy;//临时前置节点
    dummy.next=list->prt_head;//prt_head只是一个指针存地址存的是第一个节点的地址,构建一个dummy前置节点;
    LNode *prev=&dummy;//让prev扮演前置节点
    while (prev->next!=NULL) {//找尾节点
        prev=prev->next;
    }
    if (insertNode(prev,v)) {
        list->prt_head=dummy.next;//将dummy.next的值给prt_head,释放dummy,更新了prt_head;
        ++list->num;
    }
}

void insertPosList(LinkList *list, int pos, element_t v) {
    LNode dummy;
    dummy.next=list->prt_head;
    if (pos<0||pos>list->num) {
        return;
    }
    LNode *prev=&dummy;
    for (int i=0;i<=pos-1;i++) {//找到pos-1的位置,让prev向后指
        prev=prev->next;
    }
    if (insertNode(prev,v)) {
        list->prt_head=dummy.next;
        ++list->num;
    }
}

void deleteValueList(LinkList *list, element_t v) {
    LNode dummy;
    dummy.next=list->prt_head;
    LNode *prev=&dummy;//prev是删除节点的前置节点
    while (prev!=NULL&&prev->next!=NULL) {
        if (prev->next->data==v) {//找到元素v的前置节点
            break;
        }
        prev=prev->next;//移向元素v所在的节点

    }
    if (prev!=NULL&&prev->next!=NULL) {
        deleteNode(prev);
        list->prt_head=dummy.next;//更新
        --list->num;
        return;
    }
    if (prev->next==NULL&&prev->data!=v) {
        printf("delete fail\n");
        return ;
    }
}

void deleteAllLinkList(LinkList *list) {
    //以头节点为固定节点,作为删除节点的前置节点,一直删除后面的节点,直到头节点的next为NULL
    LNode dummy;
    dummy.next=list->prt_head;
    LNode *prev=&dummy;//prev是删除节点的前置节点
    while (prev->next!=NULL) {
        deleteNode(prev);
        list->prt_head=dummy.next;
        --list->num;
    }
    printf("table num=%d\n",list->num);
}

void showLinkList(const LinkList *list) {
    printf("list num=%d\n",list->num);
    LNode *start=list->prt_head;//ptr_head就是第一个节点的地址
    showNode(start);
}
/*________________________________________________________________*/
LNode *insertLink(LNode *header,element_t v) {//也可用二级指针返回值为void
    LNode dummy;
    dummy.next=header;
    LNode *prev=&dummy;
    if (insertNode(prev,v)) {
        return dummy.next;
    }
}
