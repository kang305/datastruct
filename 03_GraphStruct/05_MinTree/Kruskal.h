#ifndef DATASTRUCT2_KRUSKAL_H
#define DATASTRUCT2_KRUSKAL_H
/*m条边,n个顶点,m条边中找n-1条边(m>n-1),这n-1条边之和的权值是最小,且是生成树
约束:必须保证加入的边后,不会产生环
如何判断加入一条边后,无向图是否含有环:引入并查集
算法思路:
1.构建边集数组,进行升序排列,从小到大一一获取,满足条件:
2.加入的这条边是否会形成环路,如果形成环这条边放弃,找下一条边*/

//使用邻接矩阵来表示无向图
#include "../01_MatrixGraph/matrixGraph.h"
#include "common.h"
//从邻接矩阵中初始化边集数组
int initEdgeSet(const MGraph *graph,EdgeSet *edge);
//排序边集数组
void sortEdgeSet_pop(EdgeSet *edge,int num);
void sortEdgeSet_better(EdgeSet *edge,int num);
//Kruskal生成最小生成树
int KruskalMGraph(const MGraph *graph,const EdgeSet *edges,int num,EdgeSet *result);
int m_KruskalMGraph(const MGraph *graph,const EdgeSet *edges,int num,EdgeSet *result);

#endif //DATASTRUCT2_KRUSKAL_H
//邻接矩阵,邻接表,十字链表,邻接多重表,边集数组
/*边集数组:
 * 顶点 顺序
 * 边:多个顶点对,数组
 */