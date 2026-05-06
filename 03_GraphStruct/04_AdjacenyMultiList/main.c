#include <stdio.h>
#include "adjacencyMultiList.h"

int main() {
    int n = 5;
    char *nodeNames[] = {"V1", "V2", "V3", "V4", "V5"};
    AdjacencyMultiList *graph = createMultiList(n);
    initMultiList(graph, nodeNames, n);

    insertMultiList(graph, 0, 1, 1);
    insertMultiList(graph, 0, 3, 1);
    insertMultiList(graph, 1, 2, 1);
    insertMultiList(graph, 1, 4, 1);
    insertMultiList(graph, 2, 3, 1);
    insertMultiList(graph, 2, 4, 1);

    printf("insert %d edges!\n", graph->edgeNum);
    showMultiList(graph);
    printf("================\n");
    deleteMultiList(graph, 1, 4);
    showMultiList(graph);
    releaseMultiList(graph);
    return 0;
}