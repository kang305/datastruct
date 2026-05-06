#ifndef DATASTRUCT2_MATRIXGRAPH_H
#define DATASTRUCT2_MATRIXGRAPH_H
/*邻接矩阵:有向,无向*/
// 邻接矩阵的顶点结构，每个顶点的结构
typedef struct {
    int no;			// 顶点的编号(0--MaxNodeNum-1)
    char *show;		// 顶点的显示数据(V1,V2...)
} MatrixVertex;

// 邻接矩阵的边结构，每条边的结构，用int空间表示，既可以描述权值，也可以描述布尔值是否有边
typedef int MatrixEdge;

#define MaxNodeNum		20 //能够存的最大顶点个数
#define INF				1E4// 无穷大（表示无边）
/* 邻接矩阵的图结构 */
typedef struct {
    MatrixVertex vex[MaxNodeNum];		// 存储顶点的信息，使用一维数组
    int nodeNum;						// 约束实际顶点的个数(<MaxNodeNum)
    MatrixEdge edges[MaxNodeNum][MaxNodeNum];		// 邻接矩阵定义矩阵空间(边的权值/有无),[]内代表边的两个端点
    int directed;						// 是否是有向图 1=有向,0=无向
    int edgeNum;						// 图的实际边数
} MGraph;
/*邻接矩阵 edges[i][j] 含义：
有边：存储权值（如 1、5 等）；
无边：存储INF；
*/
void initMGraph(MGraph *graph, char *names[], int num, int directed, int edgeValue);//初始化(图,顶点名称main函数中额外定义的,个数,方向,权值)
// 将x号节点和y号节点添加一条边，权值是w，如果是无向图，自动完成y到x的赋值(无向:edges[x][y]=edges[y][x])
void addMGraphEdge(MGraph *graph, int x, int y, int w);//添加边(x节点,y节点,权值)
void visitMGraphNode(const MatrixVertex *node);//访问节点
void initMGraphVisit();//将已有的全局变量清空

void DFSMGraphTravel(const MGraph *graph, int startV);		// 深度搜索，startV起点编号
void BFSMGraphTravel(const MGraph *graph, int startV);		// 广度搜索，startV起点编号
//names[] 的下标，和 graph->vex[i].no 的值、MGraphVisited 的下标一一对应


//复现
void m_DFSMGraphTravel(const MGraph *graph, int startV);
void m_BFSMGraphTravel(const MGraph *graph, int startV);
#endif //DATASTRUCT2_MATRIXGRAPH_H
/*深度搜索:
 *要引入一个startV开始节点,因为图是m:n,需要确定开始位置
 *引入已访问节点-->辅助空间保存已经遍历的节点
 *基本思路:
 *固定顶点,访问节点,标记该节点,从这个A节点基础上,遍历跟他有关的边的情况,获得了一个节点B
 *if(该节点B是否被标记){
 *是:continue,寻找下一个未被标记的节点
 *否:访问B节点,把B节点当作新节点,再次调用深度搜索(要标记)
 *}
 */
/*广度搜索:
 * 激活了节点A,发现新的节点(以A为顶点到其他顶点B,C)-->一个顶点可以有多个任务,只能一次处理一个,处理速度<生产速度
 * 引入缓存区-->队列,引入标识数组存已经被放入过缓存区的节点
 * 节点出队时,将相连且未被访问的过的所有节点入队,不断重复此操作
 */
/*没有联系的孤立点访问:
 * 根据顶点编号访问,最后看是否还有点未访问
 */