#ifndef DATASTRUCT2_PRIM_H
#define DATASTRUCT2_PRIM_H
#include "../01_MatrixGraph/matrixGraph.h"
#include "common.h"
/*Prim算法:
 * 动态维护一个待激活顶点的边权值的数组,某个顶点到当前节点的这条边的权值信息
 * 以访问节点的visit数组,到某个顶点的另外一个顶点的坐标,构成了边
 */
int PrimMGraph(const MGraph *graph,int startV,EdgeSet *result);

int m_PrimMGraph(const MGraph *graph,int startV,EdgeSet *result);
#endif //DATASTRUCT2_PRIM_H

/*
 * Prim算法在实现时，查找阶段只关注未被激活顶点中的最小cost值，不考虑边的来源；因为来源信息已在visit数组中预先维护且保证有效。
 * 算法会遍历所有未激活顶点（包括cost为INF的），确保不遗漏，但仅选择权值最小的顶点加入生成树。
 * 这是一种职责分离的设计：查找阶段专注选择最小权值，记录阶段使用预存的visit信息构建边集
 */
