#include "joseph.h"
#include <stdlib.h>
#include <stdio.h>
void initJoseph(JosephHeader *game, int n) {
Node *node=NULL;
    for (int i = 1; i <= n; i++) {
   node = (Node*)malloc(sizeof(Node));
        node->data=i;
        if (game->head==NULL) {//第一个元素插入时head,tail都是空
            game->head=game->tail=node;
        }else {//以后的插入此时都不是空
            game->tail->next=node;//此时game->tail是node的前置节点
            game->tail=node;//尾插法将game->tail向后移
        }
        game->tail->next=game->head;//此时game->tail,就是插入节点
    }
}

void startJoseph(JosephHeader *game, int k) {
    /*法1cur和pre双指针必须找到前置节点才可以删除*/
    Node *pre=NULL;//指向待删除节点的前一个节点
    Node *cur=game->head;//此时报数的人
   while (cur->next!=cur) {//当只有一个元素的时候退出
       pre=cur;//保险
       //按照k值报数
       for (int i=1;i<k;++i) {//结束循环的时候cur刚好指向要删除节点
           pre=cur;//让pre始终指向cur前一个节点
           cur=cur->next;
       }
       //使用pre删除后一个节点
       pre->next=cur->next;//pre->next指向删除结点的后一个节点
       printf("%d ",cur->data);
       free(cur);
       cur=pre->next;//让pre始终指向cur前一个节点
   }
    printf("the last person:%d\n",cur->data);
    free(cur);
    game->tail=game->head=NULL;
    /*法2只用一个指针*/
   /*
    Node* p = game->head;//p指向起始位置
    while (1)
    {
        int i = 0;
        for (i = 1; i < k - 1; i++)//找到第k-1的人
        {
            p = p->next;
        }
        if (p->next == p)//当循环链表只剩下一个元素
        {
            printf("end : %d", p->data);
            break;
        }
        //删除操作
        Node* tmp = p->next;//让tmp临时接删除节点,p此时是删除节点的前置节点
        p->next = tmp->next;//p指向删除节点的后一个节点
        p = p->next;//p向后移一位,重新开始
    }
    */
}

void showJoseph(const JosephHeader *game) {
    Node *p=game->head;
    do {
        printf("%d\t",p->data);
        p=p->next;
    }while (p!=game->head);
 printf("\n");
}

/* 以下是几组约瑟夫环的测试答案，包括每个被杀者的顺序编号和最后的幸存者:
 * 当n=5，k=2时，被杀者的顺序编号为2, 4, 1, 5，最后的幸存者是3。
 * 当n=10，k=3时，被杀者的顺序编号为3, 6, 9, 2, 7, 1, 8, 5, 10，最后的幸存者是4。
 * 当n=7，k=2时，被杀者的顺序编号为2, 4, 6, 1, 5, 3，最后的幸存者是7。
 * 当n=10，k=17时，最后的幸存者是3。
 */
