#include "insertSort.h"

/* 默认的插入排序:
 * 1. 默认第一个元素是有序的，那么从第二个元素开始和前面有序区的值进行比较
 * 2. 待插入的元素i，和已经有序的区域从后往前依次查找
 *    若插入的元素<已经有序区域的值，则有序区域的值后移一位
 */
void insertSortV1(SortTable *table) {
   // 外层循环：从第二个元素开始遍历到最后一个元素（索引1到length-1）
   for (int i = 1; i < table->length; i++) {   // [1, n-1]
      // 如果当前元素比前一个元素小，才需要插入，否则已经有序
      if (table->data[i].key < table->data[i-1].key) {
         // 用j辅助索引来找到待插入元素的真正位置，i的值不变，i指向待排序的索引号
         int j = i - 1;                      // j指向当前有序区的最后一个元素
         Element tmp = table->data[i];       // 备份待插入的元素（哨兵）

         // 查找插入位置：在有序区[0...i-1]中从后往前查找，j > -1为临界条件
         // 只要备份值比当前比较的有序区元素小，就继续往前查找
         while (j > -1 && tmp.key < table->data[j].key) {
            table->data[j + 1] = table->data[j];  // 将比tmp大的元素向后移动一位
            --j;                                 // 向前移动比较位置
         }

         // 找到插入位置：后移--j,找到位置后此时j的位置向前了(--j),所以插入时j+1,才是tmp插入位置
         // 由于j+1的元素已经移动到后面，所以可以直接插入
         table->data[j + 1] = tmp;
      }
      // 如果待插入的元素比之前有序区域的最大值还要大，那么i位置就是这个元素的位置，无需移动
   }
}

/* 插入排序的第二种实现（交换版本）
 * 等价于扑克牌摸牌的效果，不断和前面的元素交换
 * 与版本1的主要区别：通过不断交换相邻元素来实现插入，而不是先移动后插入
 */
void insertSortV2(SortTable *table) {
   // 外层循环：从第二个元素开始遍历
   for (int i = 1; i < table->length; i++) {
      Element e = table->data[i];            //备份当前待插入元素
      int j;                                 //用于内层循环的索引

      // 内层循环：从当前位置i向前遍历，直到找到插入位置
      // 条件：j>0 确保不越界，且当前元素比前一个元素小才交换
      for (j = i; j > 0 && e.key < table->data[j-1].key; --j) {
         // 交换相邻元素，相当于将较大元素向后移动
         swapElement(&table->data[j-1], &table->data[j]);
      }
      table->data[j] = e;  //这一行可以不加，因为在循环中已经通过交换将元素放到了正确位置,但加上它可以保证逻辑完整性：将备份的元素放到最终位置
   }
}

/* 希尔排序（Shell Sort）
 * 基于插入排序的改进，通过分组进行预处理，让元素大跨度移动
 * 1. 首先按照gap（步长）进行分组
 * 2. 对每个分组进行插入排序
 * 3. 不断减小gap，直到gap=1（此时就是普通的插入排序）
 * 4. 由于前期已经使数组基本有序，最后一步插入排序的效率很高
 */
void shellSort(SortTable *table) {
   // 外层循环：按照gap进行分组，gap初始为长度的一半，每次减半直到为0
   // 这是希尔排序的增量序列，这里使用的是希尔原始序列（N/2, N/4, ..., 1）
   for (int gap = table->length / 2; gap > 0; gap = gap / 2) {
      // 对每个分组进行插入排序，这里使用的是多个分组交替进行的方式
      // 从第gap个元素开始，对所有元素进行跨度为gap的插入排序
      for (int i = gap; i < table->length; i++) {
         Element e = table->data[i];        // 备份当前待插入元素
         int j;                             // 用于内层循环的索引

         // 内层循环：对当前元素在其所在分组中进行插入排序
         // 条件：j >= gap 确保不越界，且当前元素比同组前一个元素小才交换
         // 注意这里的步长是gap，而不是1（普通插入排序的步长是1）
         for (j = i; j >= gap && e.key < table->data[j-gap].key; j -= gap) {
            // 交换间隔为gap的两个元素
            swapElement(&table->data[j-gap], &table->data[j]);
         }

         // 这一行可以不加，因为在循环中已经通过交换将元素放到了正确位置
         table->data[j] = e;
      }
   }
}

//复现
void m_insertSortV1(SortTable *table) {
   for (int i=1;i<table->length;i++) {
      if (table->data[i].key<table->data[i-1].key) {
         int j=i-1;
         Element tmp = table->data[i];
         while (j>-1&&tmp.key<table->data[j].key) {
            table->data[j+1] = table->data[j];
            j--;
         }
         table->data[j+1] = tmp;
      }
   }
}
void m_insertSortV2(SortTable *table) {
   for (int i=1;i<table->length;i++) {
      Element e = table->data[i];
      int j;
      for (j=i;j>0&&e.key<table->data[j-1].key; j--) {
         swapElement(&table->data[j-1], &table->data[j]);
      }
   }
}
void m_shellSort(SortTable *table) {
   for (int gap=table->length/2;gap>0;gap/=2) {
      for (int i=gap;i<table->length;i++) {
         Element e = table->data[i];
         int j;
         for (j=i;j>=gap&&e.key<table->data[j-gap].key;j-=gap) {
            swapElement(&table->data[j-gap], &table->data[j]);
         }
      }
   }
}