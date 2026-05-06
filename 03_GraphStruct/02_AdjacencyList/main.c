#include <stdio.h>
#include "adjacencyList.h"

void setupGraph(AGraph *graph) {
    char *names[] = {"A", "B", "C", "D", "E"};
    initAGraph(graph, names, sizeof(names)/sizeof(names[0]), 1);
    //下标从0开始所有都要减1
    addAGraph(graph, 0, 4, 1);//A->E
    addAGraph(graph, 0, 3, 1);//A->D
    addAGraph(graph, 0, 1, 1);//A->B
    addAGraph(graph, 1, 4, 1);//B->E
    addAGraph(graph, 1, 2, 1);//B->C
    addAGraph(graph, 2, 0, 1);//C->A
    addAGraph(graph, 3, 2, 1);//D->C
}

int main() {
    int n = 5;
    AGraph *graph = createAGraph(n);
    setupGraph(graph);
    printf("edge num: %d\n", graph->edgeNum);
    printf("DFS: ");
    DFSAGraphTravel(graph, 0);
    resetAGraphVisited(graph);
    printf("\nBFS: ");
    // BFSAGraphTravel(graph, 0);
    m_BFS(graph, 0);
    releaseAGraph(graph);
    return 0;
}