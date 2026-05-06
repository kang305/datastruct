#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniHeap.h"

// 创建最小堆
MiniHeap *createMiniHeap(int n) {
    // 分配堆管理结构体内存
    MiniHeap *heap = (MiniHeap *)malloc(sizeof(MiniHeap));
    if (heap == NULL) {
        return NULL;  // 内存分配失败返回NULL
    }

    // 分配数据存储空间：n+1是为了从下标1开始存储（堆的常用习惯）
    heap->data = malloc(sizeof(keyType) * (n + 1));
    if (heap->data == NULL) {
        free(heap);  // 数据空间分配失败，释放已分配的管理结构体
        return NULL;
    }

    // 将数据区初始化为0（可选,非必需）
    memset(heap->data, 0, sizeof(keyType) * (n + 1));

    heap->len = 0;       // 当前元素个数，0表示空堆
    heap->capacity = n;  // 最大容量

    return heap;
}

// 释放堆内存
void releaseMiniHeap(MiniHeap *heap) {
    // 安全检查：heap和heap->data不为NULL才释放
    if (heap && heap->data) {
        free(heap->data);  // 先释放数据空间
        heap->data = NULL; // 避免野指针
        free(heap);        // 再释放管理结构体
    }
}

// 上浮调整(下标就是树的节点位置)
static void shiftUp(MiniHeap *heap, int k) {
    // 循环条件：k>1（不是根节点）且父节点值大于当前节点
    while (k > 1 && heap->data[k/2] > heap->data[k]) {//父节点就是当前节点的下标除2
        // 交换当前节点和父节点
        keyType temp = heap->data[k];
        heap->data[k] = heap->data[k/2];
        heap->data[k/2] = temp;

        k /= 2;  // 更新k为父节点位置，继续向上比较
    }
}

// 插入元素到堆中
void insertMiniHeap(MiniHeap *heap, keyType e) {
    // 检查堆是否已满
    if (heap->len + 1 > heap->capacity) {//从下标1开始存，但是capacity是算上0的，所以加1
        printf("MiniHeap No Space!\n");
        return;
    }

    // 将新元素放入最后一个位置（len先+1，然后赋值）
    heap->data[++heap->len] = e;

    // 对新元素进行上浮调整，恢复堆性质
    shiftUp(heap, heap->len);
}

// 下沉调整
static void shiftDown(MiniHeap *heap, int k) {
    // 当k有左孩子时循环（完全二叉树性质）
    while (k * 2 <= heap->len) {
        int index = k * 2;  // 左孩子索引

        // 如果有右孩子且右孩子值更小，则选择右孩子(左孩子+1)
        if (index + 1 <= heap->len && heap->data[index + 1] < heap->data[index]) {
            index++;
        }

        // 如果当前节点已经小于等于较小的孩子，堆性质已满足
        if (heap->data[k] <= heap->data[index]) {
            break;
        }

        // 否则交换当前节点和较小的孩子
        keyType temp = heap->data[k];
        heap->data[k] = heap->data[index];
        heap->data[index] = temp;

        k = index;  // 更新k为下沉后的位置，继续向下调整
    }
}

// 提取堆顶最小元素
keyType extractMiniHeap(MiniHeap *heap) {
    // 检查堆是否为空
    if (heap->len <= 0) {
        printf("MiniHeap No Data!\n");
        return 0;
    }

    // 保存堆顶元素（最小值）
    keyType result = heap->data[1];

    // 用最后一个元素覆盖堆顶
    heap->data[1] = heap->data[heap->len];
    heap->len--;  // 元素数量减1

    // 对新的堆顶进行下沉调整，恢复堆性质
    shiftDown(heap, 1);

    return result;
}
//复现
static void m_shiftUp(MiniHeap *heap,int k) {
   while (k>1&&heap->data[k/2]>heap->data[k]) {
       keyType tmp=heap->data[k];
       heap->data[k] = heap->data[k/2];
       heap->data[k/2] = tmp;
       k /= 2;
   }
}
void m_inserMiniHeap(MiniHeap *heap, keyType e) {
    if (heap->len + 1 > heap->capacity) {
        return;
    }
    heap->data[++heap->len]=e;
    m_shiftUp(heap, heap->len);
}

static void m_shiftDown(MiniHeap *heap,int k) {
    while (k*2<=heap->capacity) {
        int index=k*2;
        if (index+1<=heap->len&&heap->data[index+1]<heap->data[index]) {
            index++;
        }
        if (heap->data[k]<=heap->data[index]) {
            break;
        }
        keyType temp = heap->data[k];
        heap->data[k] = heap->data[index];
        heap->data[index] = temp;
        k = index;
    }
}

keyType m_extractMiniHeap(MiniHeap *heap) {
    if (heap->len <= 0) {
        return 0;
    }
    keyType result = heap->data[1];
    heap->data[1] = heap->data[heap->len];
    heap->len--;
    m_shiftDown(heap, 1);
    return result;
}
