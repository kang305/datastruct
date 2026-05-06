/*单向链表的插入方式:先处理新节点next,再处理老节点next(让新节点先备份)*/
/*利用临时节点保存删除节点,前置节点指向先指向后置节点,在free(temp)*/
/*带头指针的,首元节点地址的链表,CRUD,引入dummy节点,充当前置节点,放到栈空间,CRUD的操作函数返回,dummy节点被释放*/
#ifndef DATASTRUCT2_LINKLIST_H
#define DATASTRUCT2_LINKLIST_H
typedef int element_t;
/*链式表 数据结构定义 定义节点*/
typedef struct link_node{
    element_t data;//存的数据
    struct link_node *next;//定义一个指向下一个节点的指针,类型是struct Link_node*/LNode*
}LNode;
/*带头节点的链表头*/
typedef struct {
    LNode header;//节点(无意义,只有用找首元节点)
    int num;//节点个数
}LinkTable;//头节点

/*带头指针的链表*/
typedef struct {
    LNode *prt_head;//只是一个存地址的指针,ptr_head就是第一个节点的地址
    int num;
}LinkList;

/*带头节点的单向链表接口*/
void insertHeadertable(LinkTable *table,element_t v);//头插法
void insertTailtable(LinkTable *table,element_t v);//尾插法
void insertPostable(LinkTable *table,int pos,element_t v);//指定pos位置插入
void deleteValuetable(LinkTable *table,element_t v);//删除指定值的节点
void deleteAllLinkTable(LinkTable *table);//删除全部节点
void showLinkTable(const LinkTable *table);//展示
/*带头指针的单向链表接口*/
void insertHeaderList(LinkList *list,element_t v);//头插法
void insertTailList(LinkList *list,element_t v);//尾插法
void insertPosList(LinkList *list,int pos,element_t v);//指定pos位置插入
void deleteValueList(LinkList *list,element_t v);//删除指定值的节点
void deleteAllLinkList(LinkList *list);//删除全部节点
void showLinkList(const LinkList *list);

/*地址传参*/
LNode *insertLink(LNode *header,element_t v);
#endif //DATASTRUCT2_LINKLIST_H