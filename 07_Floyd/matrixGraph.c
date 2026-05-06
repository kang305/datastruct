#include "matrixGraph.h"
#include <stdio.h>
#include <string.h>
static int isEdge(int weight) {// 判断权值是否代表有效边
    if (weight>0 &&weight<INF) {//边的权值>0且<INF代表有边
        return 1;
    }
    return 0;
}

void initMGraph(MGraph *graph, char *names[], int num, int directed, int edgeValue) {//初始化邻接矩阵(图,顶点名称main函数中额外定义的,个数,方向,权值)
    graph->directed = directed;//初始化是否有向
    graph->edgeNum=0;//开始边数为0
    graph->nodeNum=num;// graph->nodeNum设置为实际顶点数(names数组元素个数)

  for (int i = 0; i < num; i++) {
      graph->vex[i].no=i;//给顶点的编号赋值（0~num-1）
      graph->vex[i].show=names[i];//给顶点的数据赋值(指针赋值而非字符串copy)
      for (int j = 0; j < num; j++) {// 初始化当前顶点与所有顶点的边为初始值（默认无边）
          graph->edges[i][j]=edgeValue;//初始化邻接矩阵
      }
   }
}

//给边添加权值/有无
void addMGraphEdge(MGraph *graph, int x, int y, int w) {//添加边(x节点,y节点,权值)
    // 边界校验（顶点x/y需在0~nodeNum才是有效范围）
    if (x<0||x>graph->nodeNum) {
        return;
    }
    if (y<0||y>graph->nodeNum) {
        return;
    }
    if (!isEdge(graph->edges[x][y])) {//此时两个目标顶点中间没边-->添加边的有无/权值
        graph->edges[x][y]=w;
        if (graph->directed==0) {//无向图时对角线对称位置相同
            graph->edges[y][x]=w;
        }
        graph->edgeNum++;//总边数+1
    }
}

void visitMGraphNode(const MatrixVertex *node) {
    printf("\t%s",node->show);
}

static int MGraphVisited[MaxNodeNum];//记录已访问的顶点
void DFSMGraphTravel(const MGraph *graph, int startV) {//深度搜索
    //访问起点
    visitMGraphNode(&graph->vex[startV]);//graph->vex[startV]只是一个结构体,调用的函数参数是指针需要传结构体地址,所以需要加&
    //起点位置访问后标记为1(避免重复访问-->进入循环后第一次是不会进入递归函数)
    MGraphVisited[startV]=1;
    //从startV开始,找到一个边节点,再通过这个节点找下一个,DFS
    //为什么i<graph->nodeNum:每次递归都遍历图中所有顶点（编号 0 ~ graph->nodeNum-1），逐一检查「当前顶点 startV」和「顶点 i」之间的关系
    for (int i=0;i<graph->nodeNum;i++) { // 检查所有顶点（0~nodeNum-1），遍历出当前顶点的有效邻接顶点（有边且未访问）会进行n*n次
        if (isEdge(graph->edges[startV][i])&&MGraphVisited[i]==0) {//有边且未被访问,MGraphVisited[i]==0代表还未被访问过
            //检查到自己(startV)时再进循环时MGraphVisited[startV]就已经标记为1,不会再进行递归;自己和自己不会有边,edges[startV][i]不会成立,也不进行递归
            DFSMGraphTravel(graph, i);
        }
    }
}


void BFSMGraphTravel(const MGraph *graph, int startV) {//广度搜索
    int queue[MaxNodeNum];//创建队列(缓冲区)用于存顶点
    int rear=0,front=0;// 循环队列的队尾/队头指针（初始都为0，队空）
    // 起始顶点入队：循环队列先移指针再存值:避免队空/队满判定冲突
    rear=(rear+1)%MaxNodeNum;//队尾指针后移
    queue[rear]=startV;//起点入队
    MGraphVisited[startV]=1;//标记已经访问节点(避免重复访问)
    while(front!=rear) {//队列不为空
        // 队头出队：先移指针再取值
        front=(front+1)%MaxNodeNum;//队头指针后移
        int cur=queue[front];//存下当前队头元素编号(出队)
        visitMGraphNode(&graph->vex[cur]);//访问队头元素
        //BFS 里的 i < graph->nodeNum 和 DFS 里的这个逻辑完全一致--邻接矩阵遍历所有有效顶点(见上)
        for (int i=0;i<graph->nodeNum;i++) { // 检查所有顶点（0~nodeNum-1），遍历出当前顶点的有效邻接顶点（有边且未访问）
            if (isEdge(graph->edges[cur][i])&&MGraphVisited[i]==0) {//当前顶点cur与i有边且未被访问的才可以入队
                //开始让满足条件的顶点入队,并标记,for循环结束后继续while开始出队
               rear=(rear+1)%MaxNodeNum;
                queue[rear]=i;
                MGraphVisited[i]=1;
            }
        }
    }
}
//每次遍历（DFS/BFS）前需调用，避免上次遍历的标记影响结果
void initMGraphVisit() {//将MGraphVisited[MaxNodeNum]重新初始化,让其节点设置为未被访问的(MGraphVisited[MaxNodeNum]=0)
    memset(MGraphVisited, 0, sizeof(MGraphVisited));
}

//复现
  void m_DFSMGraphTravel(const MGraph *graph, int startV) {
     visitMGraphNode(&graph->vex[startV]);
     MGraphVisited[startV]=1;
     for (int i=0;i<graph->nodeNum;i++) {
         if (isEdge(graph->edges[startV][i])&&MGraphVisited[i]==0) {
             m_DFSMGraphTravel(graph,i);
         }
     }
  }

 //复现
  void m_BFSMGraphTravel(const MGraph *graph, int startV) {
    int queue[graph->nodeNum];
    int rear=0,front=0;
    rear=(rear+1)%graph->nodeNum;
    queue[rear]=startV;
    MGraphVisited[startV]=1;
    while (front!=rear) {
        front=(front+1)%graph->nodeNum;
        int cur=queue[front];
        visitMGraphNode(&graph->vex[cur]);
        for (int i=0;i<graph->nodeNum;i++) {
            if (isEdge(graph->edges[cur][i])&&MGraphVisited[i]==0) {
                rear=(rear+1)%graph->nodeNum;
                queue[rear]=i;
                MGraphVisited[i]=1;
            }
        }
    }
  }

