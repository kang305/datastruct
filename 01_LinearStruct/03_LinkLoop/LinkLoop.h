
#ifndef DATASTRUCT2_LINKLOOP_H
#define DATASTRUCT2_LINKLOOP_H
typedef int element_t;
/*定义节点*/
typedef struct Link_node {
    element_t data;
    struct Link_node *next;
}LNode;
/*链表头*/
typedef struct {
    LNode header;//
    int num;
    LNode *rear;
}LinkLoop;
/*接口设置*/
//静态初始化表头
void initLinkLoop(LinkLoop *link_loop);
//插入,头插法尾插法
void insertLinkLoopHeader(LinkLoop *link_loop,element_t v);
void insertLinkLoopRear(LinkLoop *link_loop,element_t v);
//遍历
void showLinkLoop(const LinkLoop *link_loop);
//删除
int deleteLinkLoop(LinkLoop *link_loop,element_t v);
//清空
void deleteAllLinkLoop(LinkLoop *link_loop);
/*---------------------------------------------------*/

#endif //DATASTRUCT2_LINKLOOP_H