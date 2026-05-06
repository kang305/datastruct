#include "keyPath.h"

AGraph *setupAGraph() {
    char *names[] = {
        "V0", "V1", "V2", "V3",
        "V4", "V5", "V6", "V7", "V8"
    };
    int n = sizeof(names) / sizeof(names[0]);
    AGraph *graph = createAGraph(n);
    initAGraph(graph, names, n, 1);

    addAGraph(graph, 0, 1, 6);
    addAGraph(graph, 0, 2, 4);
    addAGraph(graph, 0, 3, 5);
    addAGraph(graph, 1, 4, 1);
    addAGraph(graph, 2, 4, 1);
    addAGraph(graph, 3, 5, 2);
    addAGraph(graph, 4, 6, 9);
    addAGraph(graph, 4, 7, 7);
    addAGraph(graph, 5, 7, 4);
    addAGraph(graph, 6, 8, 2);
    addAGraph(graph, 7, 8, 4);

    return graph;
}

int main() {
    AGraph *graph = setupAGraph();
    keyPath(graph);
    releaseAGraph(graph);
}