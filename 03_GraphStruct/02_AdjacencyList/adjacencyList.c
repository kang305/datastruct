#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacencyList.h"

AGraph *createAGraph(int n) {//图中有n个节点
	AGraph *graph = malloc(sizeof(AGraph));//申请图结构
	if (graph == NULL) {
		return NULL;
	}
	graph->edgeNum = 0;//初始化边数为0
	graph->nodeNum = n;//初始化节点个数为0
	graph->nodes = malloc(sizeof(ArcNode) * n);//申请顶点空间
	graph->visited = malloc(sizeof(int) * n);//申请已经访问顶点的集合
	if (graph->nodes == NULL||graph->visited == NULL) {
		return NULL;
	}
	// 初始化刚刚申请的空间
	memset(graph->nodes, 0, sizeof(ArcNode) * n);
	memset(graph->visited, 0, sizeof(int) * n);
	return graph;
}

void visitAGraphNode(const ArcNode *node) {
	printf("\t%s", node->show);
}

void releaseAGraph(AGraph *graph) {
	int count = 0;      // 用于统计释放的边数量
	ArcEdge *tmp;       // 临时指针，用于释放边节点
	if (graph != NULL) {
		for (int i = 0; i < graph->nodeNum; i++) {//遍历所有顶点
			ArcEdge *edge = graph->nodes[i].firstEdge;//获取该顶点的第一条边
			while (edge!=NULL) {
				tmp=edge;     //保存当前该顶点的第一条边
				edge=edge->next;//edge后移
				free(tmp);      //释放第一条边
				count++;        //释放边数++
			}
		}
		printf("release %d edges!\n",count);
         free(graph->nodes);    // 释放节点数组内存
		free(graph->visited);   // 释放访问标记数组内存
	}
	free(graph);
}

void initAGraph(AGraph *graph, char *names[], int num, int directed) {
	graph->directed = directed;
	for (int i = 0; i < num; ++i) {
		graph->nodes[i].no = i;
		graph->nodes[i].show = names[i];
		graph->nodes[i].firstEdge = NULL; // 初始化节点的第一条边指针为NULL
	}
}

static ArcEdge *createArcEdge(int v, int w) {// v: 边指向的节点编号
	ArcEdge *edge = malloc(sizeof(ArcEdge));
	if (edge == NULL) {
		return NULL;
	}
	edge->no = v;
	edge->weight = w;
	edge->next = NULL;
	return edge;
}

void addAGraph(AGraph *graph, int x, int y, int w) {//x指向y
	if (x < 0 || x >= graph->nodeNum || y < 0 || y >= graph->nodeNum) {//保证x,y代表的节点索引有效
		return;
	}
	if (x == y) {//自己不能指向自己(不允许自环)
		return;
	}
	// 链表添加，头插法
	ArcEdge *edge = createArcEdge(y, w);    // 创建从x指向y的边
	edge->next = graph->nodes[x].firstEdge;//新边的next指向顶点X原来的第一条边,新边成为第一条边(头插法)
	graph->nodes[x].firstEdge = edge;//更新节点x的第一条边为新创建的边(更新firstEdge,始终指向第一个出度顶点)
	graph->edgeNum++;
	if (graph->directed == 0) {		// 无向图
		edge = createArcEdge(x, w);   // 如果是无向图，还需要添加反向边（y指向x）
		edge->next = graph->nodes[y].firstEdge; // 使用头插法将边插入到顶点y的邻接表中
		graph->nodes[y].firstEdge = edge;  //更新firstEdge
		graph->edgeNum++;
	}
}

//复现
void m_addAGraph(AGraph *graph, int x, int y, int w) {
	if (x<0||x>graph->nodeNum||y<0||y>graph->nodeNum) {
		return;
	}
	if (x==y) {
		return;
	}
	ArcEdge *edge=createArcEdge(y,w);
	edge->next=graph->nodes[x].firstEdge;
	graph->nodes[x].firstEdge=edge;
	graph->edgeNum++;
	if (graph->directed==0) {
		edge=createArcEdge(x,w);
		edge->next=graph->nodes[y].firstEdge;
		graph->nodes[y].firstEdge=edge;
		graph->edgeNum++;
	}
}

/*深度搜索:
1.检查当前邻居p->no是否已访问
2.如果未访问，递归进入该邻居（深入探索）
3.递归完全结束后，回到当前节点
4.然后执行p = p->next，移动到下一个邻居
 */
void DFSAGraphTravel(const AGraph *graph, int v) {
	graph->visited[v] = 1;   //先标记v顶点为已经访问
	visitAGraphNode(&graph->nodes[v]);//访问v顶点
	ArcEdge *p = graph->nodes[v].firstEdge;  // 获取当前节点的第一条边
	while (p) {
		if (graph->visited[p->no] == 0) {//p->no就是该顶点指向的第一个顶点编号,检查是否已经被访问
			DFSAGraphTravel(graph, p->no);
		}
		p = p->next; // 移动到下一个邻接节点
	}
}
void m_DFS(AGraph *graph,int v) {
	graph->visited[v]=1;
	visitAGraphNode(&graph->nodes[v]);
	ArcEdge *p=graph->nodes[v].firstEdge;
	while (p!=NULL) {
		if (graph->visited[v]==0) {
			m_DFS(graph,p->no);
		}
		p=p->next;
	}
}

/*广度搜索:
1. 将起始节点v入队，并标记为已访问
2. 当队列不为空时，循环以下步骤：
   a. 出队一个节点cur
   b. 访问节点cur
   c. 遍历节点cur的所有邻居：
	  1. 检查当前邻居p->no是否已访问
	  2. 如果未访问，将其入队并标记为已访问
	  3. 执行p = p->next，移动到下一个邻居
3. 释放队列内存
 */

void BFSAGraphTravel(const AGraph *graph, int v) {
  int *queue = malloc(sizeof(int) * graph->nodeNum);//创建队列
	int rear=0,front=0;
	rear=(rear+1)%graph->nodeNum;//将第一个元素编号加入队列
	queue[rear] = v;
	graph->visited[v] = 1;//标记顶点
	while (front!=rear) {//队列不为空
		front = (front+1)%graph->nodeNum;//开始出队
	   int cur=queue[front];;//作为临时存出队顶点的索引
		visitAGraphNode(&graph->nodes[cur]);
		ArcEdge *p = graph->nodes[cur].firstEdge;// 获取当前出队顶点的第一条边
		while (p!=NULL) {//让该顶点的所有邻接表元素全部入队
			if (graph->visited[p->no] == 0) {//未被访问
				rear = (rear+1)%graph->nodeNum;
				queue[rear] = p->no;
				graph->visited[p->no] = 1;//标记入队元素
			}
			p = p->next;
		}
	}
	free(queue);
	printf("\n");
}
void m_BFS(AGraph *graph,int v) {
	int *queue=malloc(sizeof(int)*graph->nodeNum);
	int rear=0,front=0;
	//开始入队
	rear=(rear+1)%graph->nodeNum;
	queue[rear] = v;
	graph->visited[v] = 1;
	while (front!=rear) {
		front=(front+1)%graph->nodeNum;
		int tmp=queue[front];
		visitAGraphNode(&graph->nodes[tmp]);
		ArcEdge *p=graph->nodes[tmp].firstEdge;
		while (p!=NULL) {
			if (graph->visited[p->no]==0) {
				rear=(rear+1)%graph->nodeNum;
				queue[rear] = p->no;
				graph->visited[p->no] = 1;
			}
			p=p->next;
		}
	}
	free(queue);
	printf("\n");
}

// 重置图中所有节点的访问标记
void resetAGraphVisited(AGraph *graph) {
	memset(graph->visited, 0, sizeof(int) * graph->nodeNum);
}
