#include <stdio.h>
#include "crossLinkGraph.h"

void setupGraph(CrossGraph *graph) {
    char *node_names[] = {"V0", "V1", "V2", "V3"};
    initCrossGraph(graph, node_names, sizeof(node_names) / sizeof(node_names[0]));
     m_addCrossArc(graph, 0, 3, 1);
     m_addCrossArc(graph, 1, 0, 1);
     m_addCrossArc(graph, 1, 2, 1);
     m_addCrossArc(graph, 2, 0, 1);
     m_addCrossArc(graph, 2, 1, 1);
}

int main() {
    int n = 4;
    CrossGraph *graph = createCrossGraph(n);
    if (graph == NULL) {
        return -1;
    }
    setupGraph(graph);
    printf("V0's inDegree: %d\n", inDegreeCrossGraph(graph, 0));
    printf("V0's outDegree: %d\n", outDegreeCrossGraph(graph, 0));
    releaseCrossGraph(graph);
    return 0;
}