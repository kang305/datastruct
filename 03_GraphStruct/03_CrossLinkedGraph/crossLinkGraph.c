#include "crossLinkGraph.h"
#include<stdio.h>
#include<stdlib.h>

CrossGraph * createCrossGraph(int n) {
    CrossGraph *graph=malloc(sizeof(CrossGraph));//申请图头
    if (graph==NULL) {
        return NULL;
    }
    graph->numEdge=0;
    graph->numVertex=0;
    graph->nodes=malloc(sizeof(CrossVertex)*n);//n个节点
    if (graph->nodes==NULL) {
        free(graph);
        return NULL;
    }
    return graph;
}

void releaseCrossGraph(CrossGraph *graph) {
    int num=0;//统计要释放的弧数量
    if (graph!=NULL) {
        if (graph->nodes!=NULL) {
            for (int i=0;i<graph->numVertex;i++) {// 遍历所有顶点
                ArcBox *box=graph->nodes[i].firstOut;//临时box存该顶点的第一个出度弧
                while (box != NULL) {
                    ArcBox *tmp = box;       // 备份当前弧
                    box = box->tailNext;     // box移动到下一个弧（按出度链表）
                    free(tmp);               // 释放当前备份的弧节点
                    num++;                   // 计数+1
                }
            }
           //出度弧和入度弧其实只是方向相反,所以只需要释放其中一个
            printf("releaseCrossGraph num=%d\n",num);
            free(graph->nodes);//释放顶点空间
        }
        free(graph);//释放图空间
    }
}

void initCrossGraph(CrossGraph *graph, char *names[], int num) {
    // 遍历所有顶点
    for (int i = 0; i < num; i++) {
        graph->nodes[i].show = names[i];           //设置顶点显示名称
        graph->nodes[i].no = i;                    //设置顶点编号（与数组索引一致）
        graph->nodes[i].firstIn = NULL;            //初始化入度链表(头)为空
        graph->nodes[i].firstOut = NULL;           //初始化出度链表(头)为空
    }
    graph->numVertex = num;  // 设置图的顶点数量
}

/* 添加有向弧 tail(起点)->head(终点)
 * 出度关系:tail tailNext
 * 入度关系:head headNext
 */
void addCrossArc(CrossGraph *graph, int tail, int head, int w) {
  ArcBox *box=malloc(sizeof(ArcBox));
    if (box==NULL) {
        return;
    }
    box->weight=w;
    // 使用头插法：将新弧插入到起点的出度链表头部
    box->tailVertex=tail;//新弧的弧尾
    box->tailNext=graph->nodes[tail].firstOut; // 新弧的tailNext指向原链表头
    //更新起点顶点(tail)的firstOut指向新弧
    graph->nodes[tail].firstOut=box;

    // 使用头插法：将新弧插入到终点的入度链表头部
    box->headVertex=head;//新弧的弧头
    box->headNext=graph->nodes[head].firstIn; // 新弧的headNext指向原链表头
    // 更新终点顶点(head)的firstIn指针指向新弧
    graph->nodes[head].firstIn=box;
}

//计算指定顶点的入度（有多少条边指向该顶点）
int inDegreeCrossGraph(CrossGraph *graph, int no) {
    int count=0;
    ArcBox *box=graph->nodes[no].firstIn;//找到该顶点的入度链表头
    while (box != NULL) {
        count++;                     // 计数+1
        box = box->headNext;         // 移动到链表下一个节点（按入度关系）
    }
    return count;
}

// 计算指定顶点的出度（从该顶点出发有多少条边）
int outDegreeCrossGraph(CrossGraph *graph, int no) {
    int count=0;
    ArcBox *box=graph->nodes[no].firstOut;//找到该顶点的出度链表头
    // 遍历整个出度链表
    while (box != NULL) {
        count++;                     // 计数+1
        box = box->tailNext;         // 移动到链表下一个节点（按出度关系）
    }
    return count;
}

//复现
void m_addCrossArc(CrossGraph *graph,int tail,int head,int w) {
    ArcBox *box=malloc(sizeof(ArcBox));
    if (box==NULL) {
        return;
    }
    box->weight=w;
    box->tailVertex=tail;
    box->tailNext=graph->nodes[tail].firstOut;
    graph->nodes[tail].firstOut=box;
    box->headVertex=head;
    box->headNext=graph->nodes[head].firstIn;;
    graph->nodes[head].firstIn=box;
}