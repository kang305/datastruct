#ifndef DATASTRUCT2_ADJACENCYMULTILIST_H
#define DATASTRUCT2_ADJACENCYMULTILIST_H
/*邻接多重表:无向图*/
// 邻接多重表的边结构
/*
iVex和jVex是边连接的两个顶点，没有先后顺序之分
iNext链接到iVex顶点的边链表
jNext链接到jVex顶点的边链表
mark字段用于遍历时标记是否已处理过该边
 */
typedef struct amlEdge {
    int iVex;                   // 边的第一个顶点编号
    struct amlEdge *iNext;      // 依附于顶点i的下一条边
    int jVex;                   // 边的第二个顶点编号
    struct amlEdge *jNext;      // 依附于顶点j的下一条边
    int weight;                 // 边的权值
    int mark;                   // 遍历标记，防止重复显示/处理
} MultiListEdge;

// 邻接多重表的顶点结构
typedef struct {
    int no;                    // 顶点编号（数组索引）
    char *show;                // 顶点显示名称
    MultiListEdge *firstEdge;  // 指向该顶点的第一条边,会在插入边时更新
} MultiListVertex;

// 邻接多重表(图结构)
typedef struct {
    MultiListVertex *nodes;    // 顶点数组
    int vertexNum;             // 顶点总数
    int edgeNum;               // 边总数
} AdjacencyMultiList;

//创建图结构：分配图结构内存，分配顶点数组内存，设置顶点数和边数。
AdjacencyMultiList *createMultiList(int n);
//释放图
void releaseMultiList(AdjacencyMultiList *graph);
//初始化图：设置每个顶点的编号和名称，并将firstEdge初始化为NULL
void initMultiList(AdjacencyMultiList *graph, char *names[], int n);
//插入边：在顶点a和b之间插入一条边，使用头插法将边节点同时插入到a和b的边链表中。
int insertMultiList(AdjacencyMultiList *graph, int a, int b, int w);
//显示图：通过遍历每个顶点的边链表，并利用mark标记避免重复显示同一条边。
void showMultiList(const AdjacencyMultiList *graph);
//删除边：找到要删除的边，然后从a和b两个顶点的边链表中删除该边节点。
void deleteMultiList(AdjacencyMultiList *graph, int a, int b);

//复现
int m_insertMultiList(AdjacencyMultiList *graph, int a, int b, int w);
#endif //DATASTRUCT2_ADJACENCYMULTILIST_H
/*
1. 无向图的对称性
在无向图中：
边(0,1) 和 边(1,0) 是同一条边
没有方向概念，只有"连接关系"
因此不需要区分"出度"和"入度"
2. iVex和jVex只是标识符
iVex和jVex仅仅标识这条边连接的是哪两个顶点，它们：
没有顺序意义：可以任意赋值，iVex=0,jVex=1 和 iVex=1,jVex=0 表示同一条边
没有方向意义：不代表"从i到j"或"从j到i"
只有区分意义：标识边的两个端点
3. iNext和jNext的确定方式
插入边(0,1)时，假设我们规定：
总是让 iVex < jVex（按编号排序）
那么边(0,1)就是 iVex=0, jVex=1
 */
