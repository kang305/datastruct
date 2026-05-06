#include <stdio.h>
#include "matrixGraph.h"

void setupMGraph(MGraph *graph) {
    char *nodeNames[] = {
        "V1", "V2", "V3", "V4",
        "V5", "V6", "V7", "V8"
    };
    initMGraph(graph, nodeNames, 8, 0, 0);
    //从下标0开始存的数据,所以x和y都减1,w为权值
    addMGraphEdge(graph, 0, 1, 1);
    addMGraphEdge(graph, 0, 2, 1);
    addMGraphEdge(graph, 1, 3, 1);
    addMGraphEdge(graph, 1, 4, 1);
    addMGraphEdge(graph, 2, 5, 1);
    addMGraphEdge(graph, 2, 6, 1);
    addMGraphEdge(graph, 3, 7, 1);
    addMGraphEdge(graph, 4, 7, 1);
    addMGraphEdge(graph, 5, 6, 1);
}

int main() {
    MGraph g1;
    setupMGraph(&g1);

    printf("edge num = %d\n", g1.edgeNum);
    printf("DFS: ");
    m_DFSMGraphTravel(&g1, 0);
    initMGraphVisit();//经过DFS后全局变量MGraphVisited[MaxNodeNum]都被设置为了1(即已被访问),需要通过改函数重新初始化
    printf("\nBFS: ");
    m_BFSMGraphTravel(&g1, 0);
    return 0;
}