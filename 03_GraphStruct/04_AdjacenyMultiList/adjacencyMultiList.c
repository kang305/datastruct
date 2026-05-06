#include <stdio.h>
#include <stdlib.h>
#include "adjacencyMultiList.h"
//邻接多重表的核心操作是边操作，而不是顶点操作
AdjacencyMultiList *createMultiList(int n) {
	// 分配图结构内存
	AdjacencyMultiList *multi_list = malloc(sizeof(AdjacencyMultiList));
	// 分配顶点数组内存，大小为n个MultiListVertex顶点结构体
	multi_list->nodes = malloc(sizeof(MultiListVertex) * n);
	// 设置顶点数
	multi_list->vertexNum = n;
	// 初始化边数为0
	multi_list->edgeNum = 0;
	return multi_list;
}

void releaseMultiList(AdjacencyMultiList *graph) {
    // 如果图指针为空，直接返回 - 避免对空指针进行操作
    if (graph == NULL) {
        return;
    }
    // 如果顶点数组为空，则直接释放图结构本身
    if (graph->nodes == NULL) {
        free(graph);
        return;
    }
    // 使用标记数组来避免重复释放
    // 计算无向图最大可能边数，公式：n*(n-1)/2->用于分配足够空间存储所有边
    int maxPossibleEdges = graph->vertexNum * (graph->vertexNum - 1) / 2;
    // 分配边指针数组，用于记录所有不重复的边节点(存储所有不重复的边（MultiListEdge）的地址)
    MultiListEdge **edges = (MultiListEdge **)malloc(sizeof(MultiListEdge *) * maxPossibleEdges);
    int edgeCount = 0;  // 记录已收集到的边数

    // 如果边数组分配失败（内存不足情况）
    if (edges == NULL) {
        // 分配失败时回退到简单释放方式（可能产生重复释放）
        printf("Warning: Failed to allocate edge array, using simple free\n");
        // 遍历所有顶点
        for (int i = 0; i < graph->vertexNum; i++) {
            // 获取当前顶点的第一条边
            MultiListEdge *edge = graph->nodes[i].firstEdge;
            // 遍历当前顶点的所有边
            while (edge != NULL) {
                MultiListEdge *temp = edge;  // 临时保存当前边指针
                // 判断当前顶点是边的第一个还是第二个顶点，决定遍历方向
                if (edge->iVex == i) {
                    edge = edge->iNext;  // 当前顶点是iVex，沿iNext遍历
                } else {
                    edge = edge->jNext;  // 当前顶点是jVex，沿jNext遍历
                }
                free(temp);  // 释放边节点 - 注意：这里可能重复释放同一条边
            }
        }
    } else {
        // 边数组分配成功，收集所有不重复的边
        for (int i = 0; i < graph->vertexNum; i++) {
            // 获取顶点i的第一条边
            MultiListEdge *edge = graph->nodes[i].firstEdge;

            // 遍历顶点i的所有边
            while (edge != NULL) {
                // 检查当前边是否已在数组中（避免重复收集）
                int found = 0;
                for (int j = 0; j < edgeCount; j++) {
                    if (edges[j] == edge) {
                        found = 1;  // 已收集过，标记为找到
                        break;
                    }
                }

                // 如果没有收集过，添加到数组
                if (!found) {
                    // 检查数组是否还有空间（理论上应该足够，但安全起见）
                    if (edgeCount < maxPossibleEdges) {
                        edges[edgeCount++] = edge;  // 添加边指针并递增计数
                    }
                }

                // 移动到下一条边（根据当前顶点在边中的位置）
                if (edge->iVex == i) {
                    edge = edge->iNext;  // 当前顶点是iVex，沿iNext遍历
                } else {
                    edge = edge->jNext;  // 当前顶点是jVex，沿jNext遍历
                }
            }
        }
        // 释放所有收集到的边节点（每个边只释放一次）
        for (int i = 0; i < edgeCount; i++) {
            free(edges[i]);  // 释放边节点内存
        }
        free(edges);  // 释放边指针数组本身
    }
    // 释放顶点数组 - 先释放顶点数组再释放图结构
    free(graph->nodes);
    // 释放图结构本身 - 最后释放主结构
    free(graph);
}


void initMultiList(AdjacencyMultiList *graph, char *names[], int n) {
	for (int i = 0; i < n; ++i) {//遍历所有顶点
		graph->nodes[i].no = i;           // 设置顶点编号
		graph->nodes[i].show = names[i];  // 设置顶点显示名称
		graph->nodes[i].firstEdge = NULL; // 初始化边链表(头)为空
	}
	graph->vertexNum = n;//设置顶点个数
}

// 插入边：在顶点a和b之间插入一条边
int insertMultiList(AdjacencyMultiList *graph, int a, int b, int w) {
	//检查顶点的编号释放有效
	if (a < 0 || b < 0)
		return -1;
	// 分配边的内存
	MultiListEdge *edge = malloc(sizeof(MultiListEdge));
	edge->weight = w;
	// 处理这条边，处理a节点连接关系(头插法)
	edge->iVex = a; //设置新创建边的第一个顶点i为a
	edge->iNext = graph->nodes[a].firstEdge;//将新创建边的iNext指向原先的链表
	graph->nodes[a].firstEdge = edge;//更新i的链表头
	// 处理这条边，处理b节点连接关系(头插法)
	edge->jVex = b;  //设置新创建边的第二个顶点j为b
	edge->jNext = graph->nodes[b].firstEdge;//将新创建边的jNext指向原先的链表
	graph->nodes[b].firstEdge = edge;//更新j的链表头
//插入一条边,两边都要更新,但是边数只加1
	graph->edgeNum++;
	return 0;
}

//复现
int m_insertMultiList(AdjacencyMultiList *graph, int a, int b, int w) {
    if (a<0||b<0) {
        return -1;
    }
    MultiListEdge *edge=malloc(sizeof(MultiListEdge));
    edge->weight=w;
    edge->iVex=a;
    edge->iNext=graph->nodes[a].firstEdge;
    graph->nodes[a].firstEdge=edge;
    edge->jVex=b;
    edge->jNext=graph->nodes[b].firstEdge;
    graph->nodes[b].firstEdge=edge;
    graph->edgeNum++;
    return 0;
}


// 初始化所有边的mark标记为0（静态函数，只在文件内使用）
static void initMark(const AdjacencyMultiList *graph) {
	for (int k = 0; k < graph->vertexNum; ++k) {
		MultiListEdge *edge = graph->nodes[k].firstEdge;
		while (edge) {//edge是指向目标顶点的第一条边,一条边会有两个端点(需要判断该顶点位于边的哪一端)
			edge->mark = 0;
				// 根据顶点i在边中的位置决定遍历方向(找该顶点在第一条边的位置i or j)
			if (edge->iVex == k) {     // 检查顶点k在边中是否是iVex
				edge = edge->iNext;    // 是：沿iNext指针继续遍历
			} else {                   // 否则顶点k是jVex
				edge = edge->jNext;    // 沿jNext指针继续遍历
			}
		}
	}
}

// 显示邻接多重表: 打印图中所有边，每条边只显示一次
void showMultiList(const AdjacencyMultiList *graph) {
	initMark(graph);  // 初始化所有边的mark标记为0

	// 遍历所有顶点
	for (int k = 0; k < graph->vertexNum; ++k) {
		MultiListEdge *edge = graph->nodes[k].firstEdge;  // 获取顶点k的第一条边

		// 遍历顶点k的所有边
		while (edge && edge->mark == 0) {  // 只处理未标记的边
			// 显示边：格式为 <顶点i名称 --- 顶点j名称>
			printf("<%s --- %s>\n", graph->nodes[edge->iVex].show,
			    graph->nodes[edge->jVex].show);
			edge->mark = 1;  // 访问的边标记为已处理，避免重复显示

			// 根据顶点k在边中的位置决定遍历方向
			if (edge->iVex == k) {  // 顶点k是边的i端点
				edge = edge->iNext;  // 沿端点i的链表继续遍历
			 } else {  // 顶点k是边的j端点
				edge = edge->jNext;  // 沿端点j的链表继续遍历
			}
		}
	}
}

//删除边：删除顶点a和b之间的边,需要同时更新两个顶点的链表，并释放边节点(两个顶点都会指向这条边,因此都需要删除)
void deleteMultiList(AdjacencyMultiList *graph, int a, int b) {
    // 第一步：在顶点a的链表中找到要删除的边及其前驱
    MultiListEdge *aPreEdge = NULL;  //a顶点的前驱边指针(要删除的边在顶点a链表中的前一条边)
    MultiListEdge *aCurEdge = graph->nodes[a].firstEdge;  //a顶点的当前边指针(最终指向要删除的边)

    // 遍历a的链表，寻找连接a和b的边(边有两个端点,只能为a或b)
    while (aCurEdge && !((aCurEdge->iVex == a && aCurEdge->jVex == b) || (aCurEdge->jVex == a && aCurEdge->iVex == b))) {//不是目标删除边
        aPreEdge = aCurEdge;  // 更新前驱
        // 根据顶点a在当前边中的位置决定遍历方向
        if (aCurEdge->iVex == a) {  // a是边的第一个端点
            aCurEdge = aCurEdge->iNext;  // 沿该链表继续
        } else {  // a是边的第二个端点
            aCurEdge = aCurEdge->jNext;  // 沿此链表继续
        }
    }
    if (aCurEdge == NULL) {  // 没有找到边，直接返回
        return;
    }

    // 第二步：在顶点b的链表中找到要删除的边及其前驱(与a找到的边实际是相同)
    MultiListEdge *bPreEdge = NULL;  // b顶点的前驱边指针
    MultiListEdge *bCurEdge = graph->nodes[b].firstEdge;  // b顶点的当前边指针

    // 遍历b的链表，寻找连接a和b的边（与a的链表是同一个边）
    while (bCurEdge && !((bCurEdge->iVex == a && bCurEdge->jVex == b) || (bCurEdge->iVex == b && bCurEdge->jVex == a))) {
        bPreEdge = bCurEdge;  //更新前驱
        //根据顶点b在当前边中的位置决定遍历方向
        if (bCurEdge->iVex == b) {  //b是边的第一个端点
            bCurEdge = bCurEdge->iNext;  //沿该链表继续
        } else {  //b是边的第二个端点
            bCurEdge = bCurEdge->jNext;  //沿此链表继续
        }
    }
    if (bCurEdge == NULL) {  // 没有找到边，直接返回
        return;
    }

    // 第三步：更新顶点a的链表
    if (aPreEdge == NULL) {  // 要删除的边是a链表的第一个节点
        if (aCurEdge->iVex == a) {  // a是边的第一个端点
            graph->nodes[a].firstEdge = aCurEdge->iNext;  // a链表头指向iNext
        } else {  // a是边的第二个端点
            graph->nodes[a].firstEdge = aCurEdge->jNext;  // a链表头指向jNext
        }
    }
    else {  // 要删除的边在a链表的中间
        if (aPreEdge->iVex == a && aCurEdge->iVex == a) {  // 前驱的iVex=a且删除边的iVex=a(都位于弧的i端点)
            aPreEdge->iNext = aCurEdge->iNext;  // 前驱的iNext指向删除边的iNext
        } else if (aPreEdge->iVex == a && aCurEdge->jVex == a) {  // 前驱的iVex=a且删除边的jVex=a
            aPreEdge->iNext = aCurEdge->jNext;  // 前驱的iNext指向当前边的jNext
        } else if (aPreEdge->jVex == a && aCurEdge->iVex == a) {  // 前驱的jVex=a且删除边的iVex=a
            aPreEdge->jNext = aCurEdge->iNext;  // 前驱的jNext指向删除边的iNext
        } else {  // 前驱的jVex=a且当前边的jVex=a
            aPreEdge->jNext = aCurEdge->jNext;  // 前驱的jNext指向删除边的jNext
        }
    }

    // 第四步：更新顶点b的链表
    if (bPreEdge == NULL) {  // 要删除的边是b链表的第一个节点
        if (bCurEdge->iVex == b) {  // b是边的第一个端点
            graph->nodes[b].firstEdge = bCurEdge->iNext;  // b链表头指向iNext
        } else {  // b是边的第二个端点
            graph->nodes[b].firstEdge = bCurEdge->jNext;  // b链表头指向jNext
        }
    }
    else {  // 要删除的边在b链表的中间
        if (bPreEdge->iVex == b && bCurEdge->iVex == b) {  // 前驱的iVex=b且删除边的iVex=b
            bPreEdge->iNext = bCurEdge->iNext;  // 前驱的iNext指向删除边的iNext
        } else if (bPreEdge->iVex == b && bCurEdge->jVex == b) {  // 前驱的iVex=b且删除边的jVex=b
            bPreEdge->iNext = bCurEdge->jNext;  // 前驱的iNext指向删除边的jNext
        } else if (bPreEdge->jVex == b && bCurEdge->iVex == b) {  // 前驱的jVex=b且删除边的iVex=b
            bPreEdge->jNext = bCurEdge->iNext;  // 前驱的jNext指向删除边的iNext
        } else {  // 前驱的jVex=b且当前边的jVex=b
            bPreEdge->jNext = bCurEdge->jNext;  // 前驱的jNext指向删除边的jNext
        }
    }

    // 第五步：释放边节点并更新边数
    free(aCurEdge);  // 释放边节点（与bCurEdge是同一个节点,释放哪一个都可）
    graph->edgeNum--;  // 边数减1
}
/*以a的视角讨论四种情况(b同理):
 *    apre ---> acur         apre ---> acur       apre --->acur          apre ---> acur
 *1.  i   j--->i   j  | 2.  i   j---->i   j | 3.  i  j--->i   j   |  4.  i   j--->i   j
 *    a   x--->a   b  |     a   x---->b   a |     x  a--->b   a   |      x   a--->a   b
 */