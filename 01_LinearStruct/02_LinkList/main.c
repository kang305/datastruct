#include <stdio.h>
#include"LinkList.h"
void test01() {
    LinkTable table;//定义头节点
    table.num=0;
    table.header.next=NULL;
    for (int i=0;i<5;i++) {
        insertHeadertable(&table,i+100);//头插法
    }
    showLinkTable(&table);
    insertPostable(&table,2,500);
    showLinkTable(&table);
    deleteValuetable(&table,500);
    showLinkTable(&table);
    deleteValuetable(&table,5010);
    showLinkTable(&table);
  deleteAllLinkTable(&table);
}

void test02() {
    LinkList list;
    list.prt_head=NULL;
    list.num=0;
    for (int i=0;i<5;i++) {
        //insertHeaderList(&list,i+100);
        insertTailList(&list,i+100);
    }
    showLinkList(&list);
    insertPosList(&list,4,418);
    showLinkList(&list);
    deleteValueList(&list,418);
    showLinkList(&list);
    deleteValueList(&list,1000);
    deleteAllLinkList(&list);
}

void test03() {
    LNode *header=NULL;
    for (int i=0;i<5;i++) {
        header=insertLink(header,i+100);
    }
    LNode *p=header;//临时p存header,防止header丢失
    while (p) {
        printf("%d ",p->data);
        p=p->next;//p向后走
    }
    printf("\n");
}
int main() {
    //test01();
    //test02();
    test03();
    return 0;
}