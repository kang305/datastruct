

#ifndef DATASTRUCT2_MERGESORT_H
#define DATASTRUCT2_MERGESORT_H
#include "../sortHelper.h"

/* 归并排序包括：从上往下，从下往上：
 * 从上往下：
 *	a. 分解	--- 当前区间一分为二
 *	b. 求解	--- 递归将两个子区间a[low...mid] 和  a[mid+1...right]进行归并
 * 从下往上：
 *  合并
 */
void mergeSort(SortTable *table);
#endif //DATASTRUCT2_MERGESORT_H