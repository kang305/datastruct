#include <stdio.h>
#include "topologicalSort.h"

AGraph *setupAGraph() {
    char *names[] = {
        "0", "1", "2", "3",
        "4", "5", "6",
    };
    int n = sizeof(names) / sizeof(names[0]);

    AGraph *graph = createAGraph(n);
    if (graph == NULL) {
        return NULL;
    }
    initAGraph(graph, names, n, 1);
    addAGraph(graph, 0, 1, 1);
    addAGraph(graph, 0, 2, 1);
    addAGraph(graph, 0, 3, 1);
    addAGraph(graph, 1, 2, 1);
    addAGraph(graph, 1, 4, 1);
    addAGraph(graph, 2, 4, 1);
    addAGraph(graph, 2, 5, 1);
    addAGraph(graph, 3, 5, 1);
    addAGraph(graph, 4, 6, 1);
    addAGraph(graph, 5, 4, 1);
    addAGraph(graph, 5, 6, 1);

    return graph;
}

int main() {
    AGraph *graph = setupAGraph();
    int result = m_TopologicalSortAGraph(graph);
    printf("\n result = %d\n", result);
    releaseAGraph(graph);

    return 0;
}
