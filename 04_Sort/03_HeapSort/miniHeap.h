

#ifndef DATASTRUCT2_MINISORT_H
#define DATASTRUCT2_MINISORT_H
#include "../sortHelper.h"
// 小顶堆的结构，堆头 堆元素
typedef struct {
    keyType *data;			// 用顺序存储方式保存堆数据
    int len;				// 约束堆data域的长度，下一个待插入的位置
    int capacity;			// 最大容量
} MiniHeap;

MiniHeap *createMiniHeap(int n);
void releaseMiniHeap(MiniHeap *heap);

void insertMiniHeap(MiniHeap *heap, keyType e);//插入
keyType extractMiniHeap(MiniHeap *heap);//提取

//复现
void m_inserMiniHeap(MiniHeap *heap, keyType e);
keyType m_extractMiniHeap(MiniHeap *heap);
#endif //DATASTRUCT2_MINISORT_H
//小顶堆
//完全二叉树:顺序存储,从下标为1的位置开始存储,任意节点的下标i/2,i,2i,2i+1
/*插入元素:
 *1.在最后的位置上插入新的元素
 *2.开始上浮操作,新元素与父节点比较,如果父节点大,交换
 *3.继续和交换后节点的父节点比较
 *4.直到满足性质-->根节点<子节点,完全二叉树
 */

/*删除,提取元素:
 * 1.删除元素,结构上只能删除最后一个
 * 2.由于堆的性质,提取堆顶的元素会破坏完全二叉树的结构特性
 * 3.最后一个元素的值赋值到第一个位置
 * 下沉操作
 * 4.如果有右孩子,比较左右谁最小和根进行交换(完全二叉树从左到右,从上到下)
 */