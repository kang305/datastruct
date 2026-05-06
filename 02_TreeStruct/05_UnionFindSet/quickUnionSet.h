#ifndef DATASTRUCT2_QUICKUNIONSET_H
#define DATASTRUCT2_QUICKUNIONSET_H
#ifndef QUICK_UNION_H
#define QUICK_UNION_H
#include "common.h"
/* QuickUnion方法：每个元素只保存父编号，通过不断找父元素，最终找到根元素编号
 * 合并，查找
 */
/*父节点：在 QuickUnion 结构中，每个元素都有一个父节点（可以是它自己-->根节点），parentID[i] 存储的是元素 i 的父节点的索引。
根节点：这是一个集合的 “祖先”，它的父节点是它自己（parentID[root] == root）。一个集合有且仅有一个根节点。*/
typedef struct {
    element_t *data;
    int *parentID;			// parentID[i]表示第i个元素的父元素编号,parentID[index]存的是当前节点的父节点索引，最上的根节点的父节点就是自己
    int *size;				// size[i]表示：当第i个值为根节点时，表示这棵树的节点个数
    int n;					// 集合中有效元素的个数
    int capacity;			// 集合的总容量
} QuickUnionSet;
//同一个集合内所有元素的根节点一定相同，但父节点不一定相同
/* 定义一个链式节点，当做栈空间维护，保存路径查找过程中的节点信息 */
typedef struct set_node { // 链式栈节点（用于路径压缩时存储路径）
    int index;  //存对应子节点的索引
    struct set_node *next;
} SetNode;

QuickUnionSet* createQuickUnionSet(int capacity);
void releaseQuickUnionSet(QuickUnionSet* setQU);
// 初始化并查集，填写元素的值和构建初始化关系
void initQuickUnionSet(QuickUnionSet* setQU, const element_t *data, int n);
// 查：在并查集中，判断两个元素是不是同一个集团
int isSameQU(const QuickUnionSet* setQU, element_t a, element_t b);
// 并：在并查集中，合并两个元素
void unionQU(const QuickUnionSet* setQU, element_t a, element_t b);//有路径压缩

void unionQU2(const QuickUnionSet *setQU, element_t a, element_t b);//无路径压缩
#endif //QUICK_UNION_H
#endif //DATASTRUCT2_QUICKUNIONSET_H