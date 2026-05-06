#ifndef DATASTRUCT2_JOSEPH_H
#define DATASTRUCT2_JOSEPH_H
/*Joseph环的节点结构*/
typedef struct node {
    int data;
    struct node *next;
}Node;
/*Joseph环的表头结构,只保留头尾指针,不包含头节点*/
 typedef struct {
     Node* head;
     Node* tail;
 }JosephHeader;
//初始化环的n个节点
void initJoseph(JosephHeader *game,int n);
//按照k个步长执行Joseph环的运行
void startJoseph(JosephHeader *game,int k);
//展示
void showJoseph(const JosephHeader *game);
#endif //DATASTRUCT2_JOSEPH_H