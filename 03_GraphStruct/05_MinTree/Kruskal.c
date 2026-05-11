#include "Kruskal.h"
#include <stdlib.h>
#include <string.h>

//从邻接矩阵初始化边集数组(邻接矩阵图结构指针,边集数组指针)-->无向图,只遍历邻接矩阵上三角
int initEdgeSet(const MGraph *graph, EdgeSet *edge) {
   int k=0;//计数器，记录有效边数
   for (int i=0;i<graph->nodeNum;i++) {    //遍历每个顶点（i从0到nodeNum-1）
      for (int j=i+1;j<graph->nodeNum;j++) {
         // 遍历每个顶点的邻接边，只遍历上三角矩阵（j从i+1开始->冒泡的思路)->这样可以避免无向图中边的重复存储
         if (graph->edges[i][j]>0&&graph->edges[i][j]<INF) {//检查是否有边(>0)
            // 将边信息存储到边集数组中
            edge[k].begin=i;
            edge[k].end=j;
            edge[k].weight=graph->edges[i][j];
            k++;
         }
      }
   }
   return k;//总边数
}

void sortEdgeSet_pop(EdgeSet *edge, int num) {//实现边的升序排列(可优化)
   EdgeSet tmp;
   for (int i=0;i<num;i++) {
      for (int j=i+1;j<num;j++) {
         if (edge[i].weight > edge[j].weight) {//对边集数组中的元素进行交换
           memcpy(&tmp,&edge[i],sizeof(EdgeSet));
            memcpy(&edge[i],&edge[j],sizeof(EdgeSet));
            memcpy(&edge[j],&tmp,sizeof(EdgeSet));
         }
      }
   }
}


//比较函数，供qsort使用
static int compareEdgeSet(const void *a, const void *b) {
   const EdgeSet *ea = (const EdgeSet *)a;
   const EdgeSet *eb = (const EdgeSet *)b;
   if (ea->weight < eb->weight) return -1;
   if (ea->weight > eb->weight) return 1;
   return 0;
}

//最优化的排序函数
void sortEdgeSet_better(EdgeSet *edge, int num) {
   //对于小数据集，使用选择排序更快
   if (num <= 20) {
      //小数据使用选择排序
      for (int i = 0; i < num - 1; i++) {
         int minIdx = i;
         for (int j = i + 1; j < num; j++) {
            if (edge[j].weight < edge[minIdx].weight) {
               minIdx = j;
            }
         }
         if (minIdx != i) {
            EdgeSet temp = edge[i];
            edge[i] = edge[minIdx];
            edge[minIdx] = temp;
         }
      }
   } else {
      // 大数据使用快速排序
      qsort(edge, num, sizeof(EdgeSet), compareEdgeSet);
   }
}



//找a顶点的根节点
static int getRoot(const int *uSet, int a) {//(边集数组地址,目标顶点编号)
   while (a != uSet[a]) { //根节点的特征是：uSet[a]==a（自己是自己的父节点）
      a=uSet[a];//向上找a顶点的根节点
   }
   return a;
}


//Kruskal算法(邻接矩阵图结构指针,已排序的边集数组指针,边集数组中边的数量,存储最小生成树边的数组)
int KruskalMGraph(const MGraph *graph, const EdgeSet *edges, int num, EdgeSet *result) {
   int sum=0;//最小生成树的总权值
   //1.初始化并查集,每个顶点的编号是自己
   int *uSet=(int *)malloc(sizeof(int)*graph->nodeNum);//申请并查集存储空间,记录各个顶点的所属集团(并查集)
   for (int i=0;i<graph->nodeNum;i++) { //初始化每个顶点为一个独立的集合（自己是自己的根节点）,uSet数组下标为编号
      uSet[i]=i;
   }

   int count=0;// 计数器，记录已选入最小生成树的边数,点数-1(count=pragh->nodeNum-1)
   //2.遍历已排序的边集数组，从小到大依次处理每条边
   for (int i=0;i<num;i++) {//遍历所有边
      //获取当前边的两端顶点的根节点编号
      int a=getRoot(uSet,edges[i].begin);
      int b=getRoot(uSet,edges[i].end);
      // 如果两个端点的根节点不同，说明这条边不会形成环,将顶点a并入b集团中(quickunion)
      if (a!=b) {
         uSet[a]=b;//合并两集合
         //把该边存入结果数组
         result[count].begin=edges[i].begin;
         result[count].end=edges[i].end;
         result[count].weight=edges[i].weight;
         sum+=edges[i].weight;//更新权值
         count++;//以有边数++
         if (count==graph->nodeNum-1) {//对于连通图,最小生成树有n-1条边（n为顶点数）
            break;//提前结束循环
         }
      }
   }
   free(uSet);//释放并查集
   return sum;
}

int m_KruskalMGraph(const MGraph *graph, const EdgeSet *edges, int num, EdgeSet *result) {
   int sum=0;
   int *USet=malloc(sizeof(int)*graph->nodeNum);
   for (int i=0;i<graph->nodeNum;i++) {
      USet[i]=i;
   }
   int count=0;
   for (int i=0;i<num;i++) {
      int a=getRoot(USet,edges[i].begin);
      int b=getRoot(USet,edges[i].end);
      if (a!=b) {
         USet[a]=b;
         result[count].begin=edges[i].begin;
         result[count].end=edges[i].end;
         result[count].weight=edges[i].weight;
         sum+=edges[i].weight;
         count++;
      }
      if (count==graph->nodeNum-1) {
         break;
      }
   }
   free(USet);
   return sum;
}
