#include <stdio.h>
#include"matrixGraph.h"
#define  MAX_SIZE 10
static int dist[MAX_SIZE][MAX_SIZE]; //存储任意两点间的最短距离
static int path[MAX_SIZE][MAX_SIZE]; //存储最短路径中，到终点的前驱节点（用于路径还原）

// 初始化图结构并添加边
void initMatrixGraph(MGraph* graph) {
    // 定义顶点名称数组
    char *node_name[]={"V0","V1","V2","V3"};
    // 初始化图：节点数，有向图（1），默认边权为INF（无穷大）
    initMGraph(graph,node_name,sizeof(node_name)/sizeof(node_name[0]),1,INF);

    // 将对角线元素（自己到自己的距离）设为0
    for(int i=0;i<graph->nodeNum;i++) {
        graph->edges[i][i]=0;
    }

    // 添加有向边
    addMGraphEdge(graph,0,1,1);   // V0->V1 权值1
    addMGraphEdge(graph,0,3,4);   // V0->V3 权值4
    addMGraphEdge(graph,1,2,9);   // V1->V2 权值9
    addMGraphEdge(graph,1,3,2);   // V1->V3 权值2
    addMGraphEdge(graph,2,0,3);   // V2->V0 权值3
    addMGraphEdge(graph,2,1,5);   // V2->V1 权值5
    addMGraphEdge(graph,2,3,8);   // V2->V3 权值8
    addMGraphEdge(graph,3,2,6);   // V3->V2 权值6
}

// Floyd算法计算所有顶点对的最短路径
void shortPathFloyd(const MGraph *graph) {
    // 初始化dist和path数组
    for (int i=0;i<graph->nodeNum;i++) {
        for (int j=0;j<graph->nodeNum;j++) {
            dist[i][j] = graph->edges[i][j];  // 初始距离为图的邻接矩阵
            // 如果i到j有直接路径且不是自身，则j的前驱为i；否则设为-1表示无直接路径
            if (dist[i][j]<INF&&i!=j) {
                path[i][j]=i;
            }else {
                path[i][j]=-1;
            }
        }
    }

    // Floyd核心三重循环：动态规划思想，k为中转顶点(见图Floyd1.png)
    for (int k=0;k<graph->nodeNum;k++) {        //第一层：逐步扩展允许的中转顶点集
        //每次循环后,我们得到的是：允许使用前k+1个顶点(0,1,...,k)作为中转的最短路径,逐步构建更大的中转集
        for (int i=0;i<graph->nodeNum;i++) {    // 第二层：遍历所有可能的起点
            //i循环代表路径的起点
            //对于每个起点i，我们检查从i到所有其他顶点的最短路径
            //固定i和k，然后尝试更新i到所有j的路径
            for (int j = 0; j < graph->nodeNum; j++) { // 第三层：遍历所有可能的终点
                //j循环代表路径的终点
                //对于每一对(i,j)，我们检查：通过当前允许的中转顶点k，是否能获得更短的i->j路径
                //条件判断：检查通过k中转是否可行且更优
                if (dist[i][k] < INF && dist[k][j] < INF &&  // 可行性检查：i->k和k->j都需要有通路
                    dist[i][j] > dist[i][k] + dist[k][j]) {  // 优化检查：通过k中转是否比当前路径更短

                    // 更新最短距离
                    dist[i][j] = dist[i][k] + dist[k][j];    // 更新i到j的最短距离

                    // path[i][j]记录的是从i到j的最短路径上,j的前一个顶点
                    // 当通过k中转时，j的前一个顶点实际上是"从k到j的最短路径上j的前一个顶点",即path[k][j]
                    path[i][j] = path[k][j];
                    }// 注意：如果不满足条件，保持原来的dist[i][j]和path[i][j]不变
            } // 结束j循环：已考虑完从i出发，经过k中转，到所有j的路径
        } // 结束i循环：已考虑完从所有i出发，经过k中转的情况
    } // 结束k循环：已考虑完所有可能的中转顶点,结束
}

void m_shortPathFloyd(const MGraph *graph) {
   for (int i=0;i<graph->nodeNum;i++) {
       for (int j=0;j<graph->nodeNum;j++) {
           dist[i][j]=graph->edges[i][j];
           if (dist[i][j]<INF&&i!=j) {
               path[i][j]=i;
           }else {
               path[i][j]=-1;
           }
       }
   }

    for (int k=0;k<graph->nodeNum;k++) {
        for (int i=0;i<graph->nodeNum;i++) {
            for (int j=0;j<graph->nodeNum;j++) {
                if (dist[i][k]<INF&&dist[k][j]<INF &&dist[i][j]>dist[i][k]+dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}
// 递归打印从i到j的最短路径
void PrintPath(int i,int j) {
    if (i==j) {  // 起点等于终点时直接输出
        printf("%d ",i);
        return;
    }
    int k=path[i][j];       // 获取j的前驱节点
    PrintPath(i,k);         // 递归打印i到前驱节点的路径
    printf("%d ",j);        // 输出当前节点
}

int main() {
    MGraph graph;
    initMatrixGraph(&graph);     // 初始化图
    m_shortPathFloyd(&graph);      // 执行Floyd算法

    // 打印所有顶点对的最短距离矩阵
    for (int i=0;i<graph.nodeNum;i++) {
        for (int j=0;j<graph.nodeNum;j++) {
            printf("%2d\t",dist[i][j]);
        }
        printf("\n");
    }
    printf("======================================\n");

    // 打印前驱矩阵
    for (int i=0;i<graph.nodeNum;i++) {
        for (int j=0;j<graph.nodeNum;j++) {
            printf("%2d\t",path[i][j]);
        }
        printf("\n");
    }
    printf("======================================\n");

    // 打印从顶点1到顶点0的具体路径
    PrintPath(1,0);
    return 0;
}