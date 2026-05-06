
#include "bubbleSort.h"
/*冒泡排序:遍历n轮,每一轮发现一个最大值
 *第一次遍历范围是[0...n-1),第二次遍历范围是[0...n-2)...
 * 第j个元素与第j+1个元素进行比较交换,第一次比完后，最大值放入第n-1个位置，这个值一定不会再变
 */

void bubbleSortV1(SortTable *table) {//数据从[0,length-1]
for (int i=0;i<table->length-1;++i) {
    for (int j=0;j<table->length-1-i;++j) {
        if (table->data[j].key > table->data[j+1].key) {
            swapElement(&table->data[j], &table->data[j+1]);
        }
    }
  }
}

void bubbleSortV2(SortTable *table) {
for (int i=0;i<table->length-1;++i) {
    int flag = 1;
    for (int j=0;j<table->length-1-i;++j) {
        if (table->data[j].key > table->data[j+1].key) {
            swapElement(&table->data[j], &table->data[j+1]);
            flag = 0;
        }
    }
    if (flag==1) {
        break;
    }
  }
}

/* 引入newIndex标记交换的位置 下次冒泡时候查找区间到newIndex */
void bubbleSortV3(SortTable *table) {
    int newIndex;      // 声明变量，用于记录每趟排序中最后一次交换的位置
    int n = table->length;  // 获取待排序数组的长度，作为初始无序区边界
    do {  // 使用do-while循环，确保至少执行一趟排序
        newIndex = 0;  // 每趟开始前重置标记位置（0表示默认无交换）

        // 遍历当前无序区[0, n-1](下标)
        for (int i = 0; i < n - 1; ++i) {
            // 比较相邻元素：若前大于后则逆序
            if (table->data[i].key > table->data[i + 1].key) {
                swapElement(&table->data[i], &table->data[i + 1]);  // 交换相邻元素
                newIndex = i + 1;  // 更新最后一次交换的位置->newIndex = i + 1; 表示记录的是交换后较大的那个元素的位置(后一个)
            }
        }

        n = newIndex;  // 将无序区边界缩小到最后一次交换的位置
    } while (newIndex != 0);  // 当上一趟存在交换时继续排序（newIndex>0表示无序区未完全有序）
}

void m_bubbleSortV3(SortTable *table) {
    int newIndex;
    int n=table->length;
    do {
        newIndex = 0;
        for (int i=0;i<n-1;++i) {
            if (table->data[i].key>table->data[i+1].key) {
                swapElement(&table->data[i],&table->data[i+1]);
                newIndex=i+1;
            }
        }
        n = newIndex;
    }while (newIndex != 0);
}
/*
初始数组: [5, 3, 8, 1, 2]
初始 n = 5 (检查所有5个元素)

第1趟: 比较范围 [0,4]
    比较 5和3 → 交换 → [3,5,8,1,2]  newIndex=1
    比较 5和8 → 不换 → [3,5,8,1,2]  newIndex=1
    比较 8和1 → 交换 → [3,5,1,8,2]  newIndex=3
    比较 8和2 → 交换 → [3,5,1,2,8]  newIndex=4
结束后: n = 4 (下一趟只检查前4个)

第2趟: 比较范围 [0,3]
    比较 3和5 → 不换 → [3,5,1,2,8]  newIndex=0
    比较 5和1 → 交换 → [3,1,5,2,8]  newIndex=2
    比较 5和2 → 交换 → [3,1,2,5,8]  newIndex=3
结束后: n = 3 (下一趟只检查前3个)

第3趟: 比较范围 [0,2]
    比较 3和1 → 交换 → [1,3,2,5,8]  newIndex=1
    比较 3和2 → 交换 → [1,2,3,5,8]  newIndex=2
结束后: n = 2 (下一趟只检查前2个)

第4趟: 比较范围 [0,1]
    比较 1和2 → 不换 → [1,2,3,5,8]  newIndex=0
结束后: n = 0 → 循环结束
 */
