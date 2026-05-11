#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "topologicalSort.h"
int TopologicalSortAGraph(const AGraph *graph) {//邻接表
   //1.将有向图的所有节点的入度进行统计
   //1.1申请入度统计表
   int *inDegree=(int *)malloc(sizeof(int)*graph->nodeNum);
   if (inDegree==NULL){
      return -1;
   }
   memset(inDegree, 0, sizeof(int)*graph->nodeNum); //初始化入度数组为0
   //1.2遍历邻接表,更新入度统计表
   for (int i = 0; i < graph->nodeNum; i++) {
      if (graph->nodes[i].firstEdge!=NULL) {    //检查顶点i是否有出度边（即邻接表是否非空）
         ArcEdge *edge=graph->nodes[i].firstEdge; //获取顶点i的第一条出度边
         while (edge!=NULL) {  // 遍历顶点i的所有出度边
            ++inDegree[edge->no];
            edge=edge->next;
         }
      }
   }
   //2.从入度表里查找入度为0的顶点,放入缓存区入栈(入队)
   //一旦入栈或者入队列,这个顶点的出度消失,更新入度表,发现出现了0,自动入缓存区
   int *stack = (int *)malloc(sizeof(int)*graph->nodeNum);//申请栈空间：用于存储入度为0的顶点索引（大小等于顶点数）
   if (stack==NULL) {//申请失败
      free(inDegree);
      return -1;
   }
   int top = -1;//栈顶指针
   for (int i = 0; i < graph->nodeNum; i++) {
      if (inDegree[i]==0) {//将入度为0的节点放入缓存区中
         stack[++top]=i;//顶点i入栈
      }
   }

   //3.从缓存区中取出一个事件,处理这个节点,这个节点的出度对应的入度节点同时减少
   int count=0;//记录已处理的顶点数
   while (top!=-1) {//栈不为空
      int index = stack[top];//出栈
      top--;
      count++;
      visitAGraphNode(&graph->nodes[index]);
      //在index索引节点的出度节点更新入度表
      ArcEdge *edge=graph->nodes[index].firstEdge;  //获取刚刚出栈顶点的第一条出度边
      while (edge!=NULL) {
         --inDegree[edge->no];//将这条边指向的邻接顶点的入度减1
         if (inDegree[edge->no]==0) {  //减1后如果该邻接顶点的入度变为0，说明它的所有前置依赖都已处理，可以放入栈中等待处理
            stack[++top]=edge->no; //将该邻接顶点索引压入栈顶
         }
         edge=edge->next;
      }
   }
   free(inDegree);
   free(stack);
   if (count==graph->nodeNum) {
      return 0;//成功完成拓扑排序，无环
   }else {
      return -3; //图中有环，无法完成拓扑排序
   }
}

int m_TopologicalSortAGraph(const AGraph *graph) {
  int *inDegree=malloc(sizeof(int)*graph->nodeNum);
   memset(inDegree, 0, sizeof(int)*graph->nodeNum);
   for (int i = 0; i < graph->nodeNum; i++) {
      if (graph->nodes[i].firstEdge!=NULL) {
         ArcEdge *edge=graph->nodes[i].firstEdge;
         while (edge!=NULL) {
            ++inDegree[edge->no];
            edge=edge->next;
         }
      }
   }
   int *stack=malloc(sizeof(int)*graph->nodeNum);
   int top=-1;
   for (int i = 0; i < graph->nodeNum; i++) {
      if (inDegree[i]==0) {
         stack[++top]=i;
      }
   }
   int cnt=0;
   while (top!=-1) {
      int index=stack[top--];
      cnt++;
      visitAGraphNode(&graph->nodes[index]);
      ArcEdge *edge=graph->nodes[index].firstEdge;
      while (edge!=NULL) {
         --inDegree[edge->no];
         if (inDegree[edge->no]==0) {
            stack[++top]=edge->no;
         }
         edge=edge->next;
      }
   }
   free(inDegree);
   free(stack);
   if (cnt==graph->nodeNum) {
      return 0;
   }else {
      return -3;
   }
}
