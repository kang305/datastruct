#include "mergeSort.h"
#include<stdio.h>
#include<stdlib.h>

// 合并接口：将两个已排序的子数组合并为一个有序数组
// left: 左子数组起始索引，mid: 中间索引，right: 右子数组结束索引
static void merge(SortTable *table, int left,int mid,int right) {
    // 分配临时子空间，用于暂存两个待合并的子数组
    // n1: 左子数组元素个数,[left,mid]
    int n1 = mid - left + 1;  //左边空间的个数
    // n2: 右子数组元素个数,[mid+1,right]
    int n2 = right - mid;     //右边空间的个数
    // 为左子数组分配临时存储空间
    Element *aux1=malloc(n1*sizeof(Element));
    // 为右子数组分配临时存储空间
    Element *aux2=malloc(n2*sizeof(Element));
    // 检查内存分配是否成功
    if(aux1==NULL || aux2==NULL) {
        return;
    }
    // 填充临时空间：将左子数组复制到aux1中
    for (int i=0;i<n1;i++) {
        // 从table的left位置开始，复制n1个元素到aux1
        aux1[i]=table->data[left+i];
    }
    // 填充临时空间：将右子数组复制到aux2中
    for (int i=0;i<n2;i++) {
        // 从table的mid+1位置开始，复制n2个元素到aux2
        aux2[i]=table->data[mid+1+i];
    }
    // 对已经有序的aux1和aux2进行归并
    int i=0;    // i: 标记aux1区域的当前待比较位置索引
    int j=0;    // j: 标记aux2区域的当前待比较位置索引
    int k=left; // k: 排序填充的结果空间索引，即table里的data，从left位置开始填充
    // 双指针比较，将较小的元素先放入原数组
    // 当两个子数组都还有元素未处理时，继续比较
    while(i<n1 && j<n2) {          // 只要有一个区间遍历完就结束循环
        // 比较两个子数组当前元素的关键字大小
        if (aux1[i].key<=aux2[j].key) {
            // aux1当前元素较小或相等，将其放入原数组
            table->data[k]=aux1[i];
            i++;  // 移动aux1的指针
        }else if (aux1[i].key>aux2[j].key){
            // aux2当前元素较小，将其放入原数组
            table->data[k]=aux2[j];
            j++;  // 移动aux2的指针
        }
       k++;  // 移动结果数组的指针
    }
    // 如果左子数组还有剩余元素，将它们全部复制到原数组
    while(i<n1) {
        table->data[k++]=aux1[i++];
    }
    // 如果右子数组还有剩余元素，将它们全部复制到原数组
    while(j<n2) {
        table->data[k++]=aux2[j++];
    }
    // 释放临时分配的存储空间，防止内存泄漏
    free(aux1);
    free(aux2);
}


// 递归分解table的[left....right]区域
// 采用分治法：将数组不断二分，直到子数组只有一个元素（自然有序），然后合并
static void mergeLoop(SortTable *table, int left, int right) {
    // 递归终止条件：当左边界不小于右边界时，说明子数组只有一个元素或为空
    if (left>=right) {
        return;
    }
    // 计算中间位置索引，将数组分成两半
    int mid=(left+right)/2;

    // 后序遍历思想：先递归处理左半部分，再递归处理右半部分,最后进行操作
    mergeLoop(table,left,mid);      // 递归排序左半部分
    mergeLoop(table,mid+1,right);    // 递归排序右半部分
    // 上述[left,mid]和[mid+1,right]的区间已经分别有序，开始合并这两个有序子数组
    merge(table,left,mid,right);
}

// 归并排序的入口函数
void mergeSort(SortTable *table) {
    // 对整个数组进行归并排序，从索引0到最后一个元素
    mergeLoop(table,0,table->length-1);
}