/*有向无环*/
#ifndef DATASTRUCT2_TOPOLOGICALSORT_H
#define DATASTRUCT2_TOPOLOGICALSORT_H
#include "../02_AdjacencyList//adjacencyList.h"

int TopologicalSortAGraph(const AGraph *graph);


int m_TopologicalSortAGraph(const AGraph *graph);
#endif //DATASTRUCT2_TOPOLOGICALSORT_H
/*拓扑排序:
 * 1.找到图中入度为0的顶点(可能有多个),把这些顶点放入缓存区中(栈,队列)
 * 2.从缓存区中取出一个顶点,放入到结果集
 * 3.这个顶点的事件发生了,顶点对应的出度消失,与其他顶点的入度消失
 * 4.又会出现新的入度为0的顶点,如果出现,继续放入缓存
 * 5.重复2-3-4
 * 6.取出缓存中的所有顶点数量:a1
 * 图中顶点的总个数为:a2
 * a1==a2  没有环
 * a1<a2    有环
 * 图的表示形式:邻接表 正邻接 当前顶点的出度 引入入度表
 */
