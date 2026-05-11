#ifndef DATASTRUCT2_CROSSLINKGRAPH_H
#define DATASTRUCT2_CROSSLINKGRAPH_H
/*十字链表:有向图计算入度和出度*/
//十字链表的弧结构
typedef struct arcBox{
    int tailVertex;    // 弧尾编号（边的起始顶点,出度）
    struct arcBox* tailNext;//连接同一个起点的下一条弧（出度链表）
    int headVertex;    // 弧头编号（边的终止顶点,入度）
    struct arcBox* headNext;//连接同一个终点的下一条弧（入度链表）
    int weight;       //弧的权值
}ArcBox;

//顶点的结构
typedef struct {
    int no;                // 顶点的唯一编号（索引）
    const char *show;
    ArcBox *firstIn;       //指向以该顶点为终点的第一条弧（入度链表头）
    ArcBox *firstOut;      //指向以该顶点为起点的第一条弧（出度链表头）
}CrossVertex;

//十字链表的图头
typedef struct {
    CrossVertex *nodes;    // 顶点数组，存储所有顶点信息
    int numVertex;         // 顶点总数
    int numEdge;           // 弧/边的总数
}CrossGraph;

//创建图结构
CrossGraph* createCrossGraph(int n);
//释放图
void releaseCrossGraph(CrossGraph* graph);
//初始化图,设置顶点信息
void initCrossGraph(CrossGraph* graph,char *names[],int num);
//添加弧tail->head
void addCrossArc(CrossGraph *graph,int tail,int head,int w);
//计算no编号的入度
int inDegreeCrossGraph(CrossGraph *graph,int no);
//计算no编号的出度
int outDegreeCrossGraph(CrossGraph *graph,int no);

//复现
void m_addCrossArc(CrossGraph *graph,int tail,int head,int w);
#endif //DATASTRUCT2_CROSSLINKGRAPH_H
/*构建有向图 A→B, A→C, B→C:
顶点数组：
顶点A (0): firstOut → 弧1(A→C) → 弧0(A→B) → NULL
顶点B (1): firstIn  → 弧0(A→B) → NULL
           firstOut → 弧2(B→C) → NULL
顶点C (2): firstIn  → 弧2(B→C) → 弧1(A→C) → NULL

弧内存节点：
弧0: A→B (权值1)
  - tailNext: →弧1(A→C)   // 在A的出度链表中
  - headNext: NULL        // 在B的入度链表中（唯一指向B的边）

弧1: A→C (权值2)
  - tailNext: NULL        // 在A的出度链表中（最后一个）
  - headNext: →弧2(B→C)  // 在C的入度链表中

弧2: B→C (权值3)
  - tailNext: NULL        // 在B的出度链表中
  - headNext: NULL        // 在C的入度链表中（最后一个）
 */