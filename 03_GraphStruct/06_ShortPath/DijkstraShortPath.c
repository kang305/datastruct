#include "DijkstraShortPath.h"
#include<stdio.h>
#include<stdlib.h>
// Dijkstra算法：计算从起点到图中所有其他顶点的最短路径
void DijkstraMGraph(const MGraph *graph, int start, int dist[], int path[]) {
    int *mark=(int *)malloc(sizeof(int)*graph->nodeNum);  //分配标记数组，用于记录顶点是否已找到最短路径
    //1.激活了start后,距离dist更新,path中的start设置为-1,作为路径打印的结束标志
    for(int i=0;i<graph->nodeNum;i++) {
        dist[i]=graph->edges[start][i]; //初始距离设置为起点到各顶点的直接距离（邻接矩阵中的值）-->无边的是INF
        mark[i]=0;//初始时所有顶点都未标记
        if(dist[i]<INF) {//距离有效,将路径设置为开始顶点的编号
            path[i]=start;
        }else {
            path[i]=-1;
        }
    }
    //起点到自身的距离为0，起点没有前驱节点（设为-1），标记起点为已访问
    path[start]=-1;
    mark[start]=1;
    dist[start]=0;

    //2.找未访问的点中的最小值
    for (int i=0;i<graph->nodeNum-1;i++) {//只需要查找n-1次,确定剩余n-1个节点的最短路径信息
        //2.1在为激活的节点中,找到一个源点到其路径的最小值
          int min=INF;
          int min_index=0;
        for (int j=0;j<graph->nodeNum;j++) {  //遍历所有顶点，寻找未标记且距离最小的顶点
            if(mark[j]==0 && dist[j]<min) {
                min=dist[j];
                min_index=j;
            }
        }
        mark[min_index]=1;//将此时最小的标记
        //2.2 以刚刚找到的顶点为中转点，更新起点到其他未标记顶点的距离
        for (int j=0;j<graph->nodeNum;j++) {
            //如果顶点j未标记，且通过min_index到达j的距离比当前已知距离更短
            if(mark[j]==0 && dist[j]>dist[min_index]+graph->edges[min_index][j]) {
                dist[j]=dist[min_index]+graph->edges[min_index][j];   //更新到顶点j的最短距离
                path[j]=min_index;      //更新顶点j的前驱节点为min_index
            }
        }
    }
    free(mark);
}

// 定义一个满递增栈
void showShortPath(const int path[], int num, int end_point) {
    int *stack = malloc(sizeof(int) * num); //分配栈空间，用于反向存储路径
    int top = -1;
    // 1. 从终点开始，沿着前驱节点回溯到起点
    while (path[end_point] != -1) {//只要不是起点节点(path[i]=-1为起点节点)
        stack[++top] = end_point;
        end_point = path[end_point]; //回溯到前驱节点
    }
    stack[++top] = end_point;//将起点节点压入栈
    // 2. 弹栈打印
    while (top != -1) {
        printf("\t%d", stack[top--]);
    }
    printf("\n");
    free(stack);
}

void m_DijkstraMGraph(const MGraph *graph, int start, int dist[], int path[]) {
int *mark=malloc(sizeof(int)*graph->nodeNum);
    for (int i=0;i<graph->nodeNum;i++) {
        dist[i]=graph->edges[start][i];
        mark[i]=0;
        if (dist[i]<INF) {
            path[i]=start;
        }else {
            path[i]=-1;
        }
    }
    path[start]=-1;
    dist[start]=0;
    mark[start]=1;
    for (int i=0;i<graph->nodeNum-1;i++) {
        int min=INF;
        int min_index=0;
        for (int j=0;j<graph->nodeNum;j++) {
            if (dist[j]<min&&mark[j]==0) {
                min=dist[j];
                min_index=j;
            }
        }
        mark[min_index]=1;
        for (int j=0;j<graph->nodeNum;j++) {
            if (mark[j]==0&&dist[j]>graph->edges[min_index][j]+dist[min_index]) {
                dist[j]=graph->edges[min_index][j]+dist[min_index];
                path[j]=min_index;
            }
        }
    }
    free(mark);
}