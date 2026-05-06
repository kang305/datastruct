#include "keyPath.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

// 计算拓扑排序并同时计算ETV（最早发生时间）和LTV（最晚发生时间）
static int topologicalOrder(const AGraph *graph,int *ETV,int *LTV) {
   // 分配入度数组空间，用于记录每个顶点的入度
   int *inDegree=malloc(sizeof(int)*graph->nodeNum);//入度记录表
    // 初始化入度数组为0
    memset(inDegree,0,sizeof(int)*graph->nodeNum);

    // 1. 初始化图中所有顶点的入度记录表
    // 遍历图中所有顶点，统计每个顶点的入度
    for (int i = 0; i < graph->nodeNum; i++) {
        // 如果当前顶点有出边
        if (graph->nodes[i].firstEdge!=NULL) {
            // 该节点有边时,统计边的情况更新入度记录表
            // 获取当前顶点的第一条出边
            ArcEdge *edge = graph->nodes[i].firstEdge;
            // 遍历当前顶点的所有出边
            while (edge) {
                // 增加目标顶点的入度（edge->no表示边的终点顶点编号）
                ++inDegree[edge->no];
                // 移动到下一条出边
                edge = edge->next;
            }
        }
    }

    // 2. 将入度为0的节点入栈，出栈时就可以找到各个顶点的最早发生时间
    int top=-1; // 栈顶指针，-1表示空栈
    // 分配栈空间，用于保存入度为0的顶点
    int *stack=malloc(sizeof(int)*graph->nodeNum);
    // 分配数组空间，用于保存拓扑排序的结果
    int *topOut=malloc(sizeof(int)*graph->nodeNum);

    // 2.1 将初始化的入度表中，入度为0的顶点编号压入栈，此时这个点就是源点(只有一个)
    // 遍历所有顶点，找到第一个入度为0的顶点（源点）
    for (int i = 0; i < graph->nodeNum; i++) {
        // 如果当前顶点入度为0
        if (inDegree[i] == 0) {
            // 将顶点编号压入栈
            stack[++top]=i;
            break;//默认只有一个源点
        }
    }

    // 2.2 不断弹栈，更新入度记录表
    int tmp;//暂存从栈上弹出的顶点编号，通过这个编号的出度情况，计算ETV
    int index=0;//拓扑排序结果的索引(topOut)，用于记录已排序的顶点数量

    // 当栈不为空时，继续处理
    while (top!=-1) {
        // 弹出栈顶顶点
        tmp=stack[top--];
        // 将弹出的顶点存入拓扑排序结果数组
        topOut[index++]=tmp;

        // 获取弹出顶点的第一条出边
        ArcEdge *edge = graph->nodes[tmp].firstEdge;
       // 遍历当前顶点的所有出边
       while (edge!=NULL) {
           // 减少目标顶点的入度（相当于删除从tmp到edge->no的边）
           --inDegree[edge->no];

           // 如果目标顶点的入度变为0，将其压入栈
           if (inDegree[edge->no]==0) {
               stack[++top]=edge->no;
           }

           // 计算ETV（事件最早发生时间）：
           // 从tmp顶点的最早发生时间加上边的权值，如果大于目标顶点当前的ETV，则更新
           // 公式：ETV[v] = max{ETV[u] + weight(u,v)}，其中u是v的前驱
           if (ETV[tmp]+edge->weight>ETV[edge->no]) {//tmp顶点的值+边的权值>tmp->next顶点目前的值
               ETV[edge->no]=ETV[tmp]+edge->weight;
           }
           // 移动到下一条出边
           edge = edge->next;
       }
    }

    // 拓扑排序结束，释放不再需要的内存
    // 入度记录表结束
    free(inDegree);
    // 栈空间结束
    free(stack);

    // 检查是否有环：如果拓扑排序得到的顶点数小于图中顶点总数，说明有环
    if (index<graph->nodeNum) {//有环
        // 释放拓扑排序结果数组
        free(topOut);
        return -1; // 返回-1表示有环，计算失败
    }

    // 3. 更新LTV（事件最晚发生时间）
    // 获取拓扑排序结果的最后一个顶点编号（终点/汇点),就是topOut的栈顶元素
    tmp=topOut[--index];//获取拓扑排序结果的最后一个顶点编号

    // 3.1 初始化所有顶点的LTV为终点的ETV（终点的最早和最晚发生时间相同）
    for (int i=0;i<graph->nodeNum;i++) {//都初始化为最大值
        LTV[i]=ETV[tmp];
    }

    // 3.2 逆拓扑顺序计算LTV（从后往前遍历拓扑排序结果）
    while (index!=0) {
        // 获取前一个顶点
        int getTopNO=topOut[--index];
        // 获取当前顶点的第一条出边
        ArcEdge *edge = graph->nodes[getTopNO].firstEdge;

        // 遍历当前顶点的所有出边
        while (edge!=NULL) {
            // 计算LTV（事件最晚发生时间）：
            // 后一个节点的LTV减去入度边的权值，如果小于当前顶点的LTV，则更新
            // 公式：LTV[u] = min{LTV[v] - weight(u,v)}，其中v是u的后继,u可以有多个v
            if (LTV[edge->no]-edge->weight<LTV[getTopNO]) {//getTopNo->next顶点的值-边的权值<getTopNo的权值(从后往前)
                LTV[getTopNO]=LTV[edge->no]-edge->weight;
            }
            // 移动到下一条出边
            edge = edge->next;
        }
    }

    // 释放拓扑排序结果数组
    free(topOut);
    return 0; // 成功返回0
}

// 打印表格辅助函数，用于显示ETV和LTV数组
static void showTable(const int *table,int n,const char *name) {
    printf("%s\n",name);
    for (int i=0;i<n;i++) {
        printf("\t%d",table[i]);
    }
    printf("\n");
}

/* 关键路径算法：在AOE网中寻找关键路径
 * 为了统计出AOE网的关键路径,需要4个统计值：
 * 对于AOE网中的顶点给定两个时间：
 * ETV:事件最早发生时间   LTV:事件的最晚发生时间
 * 对于边来说有两个时间：
 * ETE:活动最早发生的时间  LTE:活动的最晚发生时间
 * 对于所有的边来说，如果它的最早发生时间等于最晚发生时间，这条边就是关键活动
 * 这些关键活动构成的路径称为关键路径
 */
void keyPath(AGraph *graph) {
    // 1. 计算顶点的ETV和LTV
    // 分配ETV（事件最早发生时间）数组空间
    int *ETV=malloc(sizeof(int)*graph->nodeNum);
    // 分配LTV（事件最晚发生时间）数组空间
    int *LTV=malloc(sizeof(int)*graph->nodeNum);

    // 检查内存分配是否成功
    if (ETV == NULL || LTV == NULL) {
        return; // 内存分配失败，直接返回
    }

    // 初始化ETV和LTV数组为0
    memset(ETV,0,sizeof(int)*graph->nodeNum);
    memset(LTV,0,sizeof(int)*graph->nodeNum);

    // 调用拓扑排序函数计算ETV和LTV
    topologicalOrder(graph,ETV,LTV);

    // 显示ETV和LTV的结果
    showTable(ETV,graph->nodeNum,"ETV: ");
    showTable(LTV,graph->nodeNum,"LTV: ");

    // 2. 计算边的ETE和LTE，直接计算关键路径
    // 遍历图中的所有顶点
    for (int i=0;i<graph->nodeNum;i++) {
        // 获取当前顶点的第一条出边
        ArcEdge *edge = graph->nodes[i].firstEdge;
        // 遍历当前顶点的所有出边
        while (edge!=NULL) {
            // 计算每条边的ETE和LTE：
            // 每个边的最早发生时间(ETE)就是边的弧尾的ETV
            // 每个边的最晚发生时间(LTE)就是边的弧头的LTV减去当前边的权值
            // 如果ETE == LTE，则该边为关键活动

            // 注意：这里比较的是边的起点i的ETV和边的终点edge->no的LTV减去边权值
            if (ETV[i] == LTV[edge->no] - edge->weight) {//ETV[i]就是弧尾, LTV[edge->no]就是弧头
                // 输出关键路径边：起点 --权重-- 终点
                printf("<%s> ---%d--- <%s>\n",
                    graph->nodes[i].show,  // 边的起点名称
                    edge->weight,         // 边的权重（活动持续时间）
                    graph->nodes[edge->no].show); // 边的终点名称
            }
            // 移动到下一条出边
            edge = edge->next;
        }
    }

    // 释放动态分配的内存
    free(ETV);
    free(LTV);
}