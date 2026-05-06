#include <stdio.h>
#include <stdlib.h>
#include "DijkstraShortPath.h"

void setupMGraph(MGraph *graph) {
    char *names[] = {"0", "1", "2", "3", "4", "5", "6"};
    initMGraph(graph, names, 7, 1, INF);

    addMGraphEdge(graph, 0, 1, 4);
    addMGraphEdge(graph, 0, 2, 6);
    addMGraphEdge(graph, 0, 3, 6);
    addMGraphEdge(graph, 1, 4, 7);
    addMGraphEdge(graph, 1, 2, 1);
    addMGraphEdge(graph, 2, 4, 6);
    addMGraphEdge(graph, 2, 5, 4);
    addMGraphEdge(graph, 3, 2, 2);
    addMGraphEdge(graph, 3, 5, 5);
    addMGraphEdge(graph, 4, 6, 6);
    addMGraphEdge(graph, 5, 4, 1);
    addMGraphEdge(graph, 5, 6, 8);
}


int main() {
    MGraph graph;
    int *dist = NULL;
    int *path = NULL;

    setupMGraph(&graph);
    dist = malloc(sizeof(int) * graph.nodeNum);
    path = malloc(sizeof(int) * graph.nodeNum);

 m_DijkstraMGraph(&graph, 0, dist, path);
    for (int i = 0; i < graph.nodeNum; ++i) {
        printf("%d\t", dist[i]);
    }
    printf("\n");
    printf("0 ~ 4 node info: ");
    showShortPath(path, graph.nodeNum, 4);
    free(dist);
    free(path);
    return 0;
}
