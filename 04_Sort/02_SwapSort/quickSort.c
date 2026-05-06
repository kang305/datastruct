#include "quickSort.h"
/* 快速排序核心思想：小 犄点 大 --> 不断缩小区间(分而治之) */

// 声明一个函数指针变量partition，可以指向不同的分区函数
// 该函数指针类型：返回int（分区后基准位置），参数为(SortTable*, int, int)
int (*partition)(SortTable *table, int startIndex, int endIndex);

// 双边分区函数（双指针法） - 从数组两端向中间扫描
static int partitionDouble(SortTable *table, int startIndex, int endIndex) {
    // 选择起始位置的元素作为基准元素（pivot）
    int pivot = startIndex;  // pivot保存基准元素的索引
    int left = startIndex;   // 左指针：从起始位置开始向右移动
    int right = endIndex;    // 右指针：从结束位置开始向左移动

    // 主循环：当左右指针未相遇时继续分区
    while (left != right) {
        // 右侧指针向左移动：寻找第一个小于等于基准值的元素
        /*
         必须先右后左:保证最后基准与left=right相等的位置交换时table->data[left]<table->data[pivot]
         先让left移可能使得左边出现比基准大的值(交换是左小右的,越往右越大,可能交换时table->data[left]>table->data[pivot])
         left指针指向的一定不大于基准,从右开始来找左,来使得相等
         */
        //  条件left < right确保指针不会交叉越界,table->data[right].key > table->data[pivot].key：当右侧元素大于基准值时继续左移
        while (left < right && table->data[right].key > table->data[pivot].key) {
            right--;  // 当前元素大于基准值，右指针左移
        }

        // 左侧指针向右移动：寻找第一个大于基准值的元素
        // 条件table->data[left].key <= table->data[pivot].key：当左侧元素小于等于基准值时继续右移
        while (left < right && table->data[left].key <= table->data[pivot].key) {
            left++;  // 当前元素小于等于基准值，左指针右移
        }

        // 如果左右指针还未相遇，交换它们所指向的元素
        // 此时arr[left] > pivot且arr[right] <= pivot，交换后小的到左边，大的到右边
        if (left < right) {
            swapElement(&table->data[right], &table->data[left]);  // 交换左右指针位置的元素
        }
        // 交换后继续循环，直到左右指针相遇
    }

    // 左右指针相遇，此时left == right，这个位置就是基准元素的正确位置
    // 将基准元素交换到这个相遇位置
    swapElement(&table->data[pivot], &table->data[left]);

    // 返回基准元素的最终位置，用于后续递归分区
    return left;
}

// 单边分区函数:
static int partitionSingle(SortTable *table, int startIndex, int endIndex) {
    // mark指针：标记小于基准值的区域的边界（最后一个小于基准值的位置）
    int mark = startIndex;
    // 保存基准值（选择第一个元素的值作为基准）
    keyType tmp = table->data[startIndex].key;  // keyType=int,tmp保存基准值

    // 遍历基准元素之后的所有元素（从startIndex+1到endIndex）
    for (int i = startIndex + 1; i <= endIndex; ++i) {
        // 如果当前元素小于基准值
        if (table->data[i].key < tmp) {
            ++mark;  // 扩展小于基准值的区域：mark指针右移一位
            // 交换mark位置和i位置的元素
            // 此时mark位置的原元素是大于等于基准值的，i位置是小值，交换后小值到左边(mark位置)
            swapElement(&table->data[mark], &table->data[i]);//mark++后是比基准大,此时i位置比基准小所以可以交换
        }
        // 注意：等于基准值的元素不会被交换，保留在右侧大于等于基准值的区域
    }

    // 循环结束后，mark位置是小于基准值的区域的最后一个位置
    // 将基准元素（在startIndex位置）交换到mark位置
    // 此时：startIndex~mark-1都小于基准值，mark位置是基准值，mark+1~endIndex都大于等于基准值
    swapElement(&table->data[mark], &table->data[startIndex]);

    // 返回基准元素的最终位置
    return mark;
}

// 快速排序递归函数 - 采用分治思想
// 排序区间为闭区间[startIndex, endIndex]
static void quickSort(SortTable *table, int startIndex, int endIndex) {
    // 递归终止条件：当起始索引不小于结束索引时，区间只有一个或零个元素
    if (startIndex >= endIndex) {
        return;  // 直接返回，无需排序
    }

    // 调用分区函数，将数组分为三部分：小于基准、基准、大于基准
    // 返回基准元素的索引号
    // 无论单边还是双边分区，都遵循同样的逻辑：以基准为界分为两个区域，
    // 然后在各自的区域内继续用同样的方法确定新的基准，不断递归缩小区域
    int pivot = partition(table, startIndex, endIndex);

    // 递归排序基准元素左侧的子数组（小于基准值的部分）
    quickSort(table, startIndex, pivot - 1);

    // 递归排序基准元素右侧的子数组（大于基准值的部分）
    quickSort(table, pivot + 1, endIndex);
}

// 双边查找法确定犄点的快排 - 对外接口函数
void quickSortV1(SortTable *table) {
    // 将函数指针partition指向双边分区函数
    partition = partitionDouble;
    // 调用递归快速排序函数，对整个数组进行排序
    quickSort(table, 0, table->length - 1);
}

// 单边查找法确定犄点的快排 - 对外接口函数
void quickSortV2(SortTable *table) {
    // 将函数指针partition指向单边分区函数
    partition = partitionSingle;
    // 调用递归快速排序函数，对整个数组进行排序
    quickSort(table, 0, table->length - 1);
}


//复现
static int m_partitionDouble(SortTable *table, int startIndex, int endIndex) {
    int pivot=startIndex;
    int left = startIndex;
    int right = endIndex;
    while (left!=right) {
        while (left<right&&table->data[right].key>table->data[pivot].key) {
            right--;
        }
        while (left<right&&table->data[left].key<=table->data[pivot].key) {
            left++;
        }
        if (left<right) {
            swapElement(&table->data[left], &table->data[right]);
        }
    }
    swapElement(&table->data[pivot], &table->data[left]);
    return left;
}

static int m_partitionSingle(SortTable *table, int startIndex, int endIndex) {
    int mark = startIndex;
    keyType tmp=table->data[startIndex].key;
    for (int i=startIndex+1; i<=endIndex; ++i) {
        if (table->data[i].key<tmp) {
            ++mark;
            swapElement(&table->data[mark], &table->data[i]);
        }
    }
    swapElement(&table->data[mark], &table->data[startIndex]);
    return mark;
}