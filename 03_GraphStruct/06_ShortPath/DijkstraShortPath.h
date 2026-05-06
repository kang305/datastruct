#ifndef DATASTRUCT2_DIJKSTRASHORTPATH_H
#define DATASTRUCT2_DIJKSTRASHORTPATH_H
/* Dijkstra算法通过邻接矩阵来进行算法设计:有向图*/
#include "../01_MatrixGraph/matrixGraph.h"
/* input: 邻接矩阵、单源点
 * output: 距离数组、路径数组，打印出单源点到指定节点的路径，到其的最短路径值
 */
//dist:描述的是源点到其他节点的距离,初始化时候只关心源点到他的邻接点的距离
//path:描述的是到该节点前是经过哪个顶点到的(打印路径信息)
//mark:描述的是该节点是否被访问
void DijkstraMGraph(const MGraph *graph, int start, int dist[], int path[]);


void m_DijkstraMGraph(const MGraph *graph, int start, int dist[], int path[]);
/* 从path信息表里打印出到end_point点的路径信息*/
void showShortPath(const int path[], int num, int end_point);//目的节点
#endif //DATASTRUCT2_DIJKSTRASHORTPATH_H