#include "Prim.h"
#include<stdio.h>
#include<stdlib.h>
/*cost数组:图中到各顶点边的权值数组
 *mark数组:图中已经激活顶点状态
 *visit数组:从哪个顶点访问当前顶点(存的是该顶点的编号)
 *startV:第一个激活的顶点编号
 */
int PrimMGraph(const MGraph *graph, int startV, EdgeSet *result) {
    int *cost=(int*)malloc(sizeof(int)*graph->nodeNum);//存储当前生成树到各顶点的最小权值
    int *mark=(int*)malloc(sizeof(int)*graph->nodeNum);//标记顶点是否已加入生成树（0=未加入，1=已加入）
    int *visit=(int*)malloc(sizeof(int)*graph->nodeNum);//记录每个顶点是从哪个顶点连接过来的
    if (cost==NULL || mark==NULL || visit==NULL) {
        return 0;
    }
    int sum=0;//最小生成树总权值之和
    //1.根据传入的startV激活当前节点,更新相关的辅助空间
   for (int i=0;i<graph->nodeNum;i++) {//遍历所有节点
       cost[i]=graph->edges[startV][i];//检查当前节点是否与startV有边,有就赋值为权值,没有则赋值为INF
       mark[i]=0;    //所有顶点初始状态都未加入生成树
       if (cost[i]<INF) {//cost中存入了边的
           visit[i]=startV; //如果顶点i与起点有边，则记录是从起点连接过来
       }else {
           visit[i]=-1;
       }
   }
    mark[startV]=1; //将起点标记为已加入生成树
    //2.动态激活顶点,直到所有的顶点被激活,逐步构建最小生成树，需要找到n-1条边
    for (int i=0;i<graph->nodeNum-1;i++) {  //查找n-1个最小生成树的边
        //从权值数组里找到未激活点里的最小值
        int mini=INF;  // 记录当前未加入顶点中的最小权值
        int index=0;  //找到的最小值的辅助空间,当前最小值的顶点编号
        //2.1从cost数组内找到未激活顶点里的最小值
        for (int j=0;j<graph->nodeNum;j++) {  //从权值数组里找到未激活顶点的最小值
            if (mark[j]==0&&cost[j]<mini) {   //顶点j未加入生成树，且到j的权值小于当前最小值
                mini=cost[j];  //更新最小值
                index=j;       //保存当前最小值的索引
            }
        }
        // 将找到的最小权值顶点加入生成树
        mark[index]=1;   //激活最小值的点
        // 2.2将这条边保存到结果数组中
        result[i].begin=index;         //边的起点
        result[i].end=visit[index];    //边的终点(从哪个顶点来的)
        result[i].weight=mini;         //边的权值
        sum+=mini;                     //累加总权值(startV作为起始顶点，没有被任何"边"引入最小生成树，所以没有对应的边权值需要累加。)
        //3.每激活一个顶点后,更新cost数组,以index为行下标,获取他到其他顶点的权值,更新cost数组
        for (int j=0;j<graph->nodeNum;j++) {
            if (mark[j]==0&&graph->edges[index][j]<cost[j]) {//(会遍历到已经标记的顶点,但他们中间的cost已经是当前最小,因此不会根据graph->edges[index][j]更新)
                cost[j]=graph->edges[index][j];  // 更新最小权值
                visit[j]=index;                  // 记录j是从index连接过来的
            }
        }
    }
    // 释放动态分配的内存
    free(cost);
    free(mark);
    free(visit);
    return sum;
}

int m_PrimMGraph(const MGraph *graph, int startV, EdgeSet *result) {
    int *cost=malloc(sizeof(int)*graph->nodeNum);
    int *mark=malloc(sizeof(int*)*graph->nodeNum);
    int *visited=malloc(sizeof(int)*graph->nodeNum);
    int sum=0;
    for (int i=0;i<graph->nodeNum;i++) {
        cost[i]=graph->edges[startV][i];
        mark[i]=0;
        if (cost[i]<INF) {
            visited[i]=startV;
        }else {
            visited[i]=-1;
        }
    }
    mark[startV]=1;
    for (int i=0;i<graph->nodeNum-1;i++) {
        int mini=INF;
        int index=0;
        for (int j=0;j<graph->nodeNum;j++) {
            if (mark[j]==0&&cost[j]<mini) {
                mini=cost[j];
                index=j;
            }
        }
        mark[index]=1;
        result[i].end=index;
        result[i].begin=visited[index];
        result[i].weight=mini;
        sum+=mini;
        for (int j=0;j<graph->nodeNum;j++) {
            if (mark[j]==0&&graph->edges[index][j]<cost[j]) {
                cost[j]=graph->edges[index][j];
                visited[j]=index;
            }
        }
    }
    free(cost);
    free(mark);
    free(visited);
    return sum;
}