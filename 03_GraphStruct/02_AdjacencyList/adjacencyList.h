#ifndef DATASTRUCT2_ADJACENCYLIST_H
#define DATASTRUCT2_ADJACENCYLIST_H
/*邻接表:有向*/
//边的结构
typedef struct arcEdge {
    int no;       //目标顶点的索引,边的终点
    int weight;   //这条边的权值
    struct arcEdge *next;//顶点的下一个出度
}ArcEdge;

//顶点的结构
typedef struct {
    int no;    //顶点编号
    char *show;//顶点显示内容
    ArcEdge *firstEdge;//指向第一个出度的节点,后续出度由边的next来指定,链表头(用于头插法)
}ArcNode;

//邻接表的图结构
typedef struct {
    ArcNode *nodes;   //图中顶点的集合
    int nodeNum;      //图中顶点的个数
    int directed;     //是否有向图
    int edgeNum;      //图中边的个数
    int *visited;     //已经访问的编号(遍历的辅助数组-->标记是否访问)
}AGraph;

//产生n个节点的邻接表的图
AGraph* createAGraph(int n);
//释放图
void releaseAGraph(AGraph *graph);
//初始化
void initAGraph(AGraph *graph,char *names[],int num,int directed);
//对x和y顶点进行连接
void addAGraph(AGraph *graph,int x,int y,int w);//xy表示进行连接的顶点
//深度遍历
void DFSAGraphTravel(const AGraph *graph,int v);
//广度遍历
void BFSAGraphTravel(const AGraph *graph,int v);
//访问顶点
void visitAGraphNode(const ArcNode *node);
//重置访问标记
void resetAGraphVisited();


//复现
void m_DFS(AGraph *graph,int v);
void m_BFS(AGraph *graph,int v);
void m_addAGraph(AGraph *graph,int x,int y,int w);
#endif //DATASTRUCT2_ADJACENCYLIST_H