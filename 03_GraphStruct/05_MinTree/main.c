#include <stdio.h>
#include <stdlib.h>
#include "Kruskal.h"
#include "Prim.h"
void setupMGraph(MGraph *graph, int edgeValue) {
    char *names[] = {
        "A", "B", "C", "D",
        "E", "F", "G",
    };
    //构建邻接矩阵
    initMGraph(graph, names, 7, 0, edgeValue);
    addMGraphEdge(graph, 0, 1, 12);
    addMGraphEdge(graph, 0, 5, 16);
    addMGraphEdge(graph, 0, 6, 14);
    addMGraphEdge(graph, 1, 2, 10);
    addMGraphEdge(graph, 1, 5, 7);
    addMGraphEdge(graph, 2, 3, 3);
    addMGraphEdge(graph, 2, 4, 5);
    addMGraphEdge(graph, 2, 5, 6);
    addMGraphEdge(graph, 3, 4, 4);
    addMGraphEdge(graph, 4, 5, 2);
    addMGraphEdge(graph, 4, 6, 8);
    addMGraphEdge(graph, 5, 6, 9);
}

int test01() {
    MGraph graph;               //图
    EdgeSet *edges;				//边集数组首地址
    int num;					//边集数组的个数
    EdgeSet *result;			//激活边的情况,存储最小生成树边的数组
    int sum;                    //权值总和

    setupMGraph(&graph, 0);
    edges = malloc(sizeof(EdgeSet) * graph.edgeNum);
    num = initEdgeSet(&graph, edges);//总有效边数
    printf("edge set num : %d\n", num);
    sortEdgeSet_better(edges, num);//给边集数组排序

    result = malloc(sizeof(EdgeSet) * (graph.nodeNum - 1));//最小生成树的边只有n-1条边
    sum = m_KruskalMGraph(&graph, edges, num, result);
    printf("Kruskal sum of weight: %d\n", sum);
    for (int i = 0; i < graph.nodeNum - 1; ++i) {
        printf("edge %d: [%s] --- <%02d> --- [%s]\n", i + 1,
            graph.vex[result[i].begin].show, result[i].weight,graph.vex[result[i].end].show);
    }
    free(edges);
    free(result);
}

void test02() {
    MGraph graph;

    setupMGraph(&graph, INF);
    EdgeSet *result = malloc(sizeof(EdgeSet) * (graph.nodeNum - 1));
    if (result == NULL) {
        return;
    }
    int sum =m_PrimMGraph(&graph, 0, result);
    printf("prim weight: %d\n", sum);
    for (int i = 0; i < graph.nodeNum - 1; ++i) {
        printf("edge %d: [%s] --- <%d> --- <%s>\n", i + 1,
            graph.vex[result[i].begin].show, result[i].weight, graph.vex[result[i].end].show);
    }
    free(result);
}

int main() {
    test01();
test02();
    return 0;
}
