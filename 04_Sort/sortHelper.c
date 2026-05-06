#include <stdio.h>  // 标准输入输出头文件，用于fprintf等函数
#include <stdlib.h> // 标准库头文件，用于malloc、free、rand、srand等函数
#include <time.h>   // 时间头文件，用于time、clock_t、clock等函数
#include <string.h> // 字符串头文件，用于memcpy函数
#include "sortHelper.h" // 自定义头文件，包含排序辅助函数和数据结构的声明

/* 交换a和b的元素值 */
void swapElement(Element *a, Element *b) {
	Element tmp;                    // 声明临时Element变量tmp，用于交换时的临时存储
	memcpy(&tmp, a, sizeof(Element));  // 将a指向的Element数据拷贝到tmp中
	memcpy(a, b, sizeof(Element));     // 将b指向的Element数据拷贝到a指向的位置
	memcpy(b, &tmp, sizeof(Element));  // 将tmp中存储的数据拷贝到b指向的位置
}

/* 产生n个随机数的排序表，值的范围是[low, high] */
SortTable *generateRandomArray(int n, int low, int high) {
	SortTable *table = (SortTable *) malloc(sizeof(SortTable));  // 为SortTable结构体分配内存
	if (table == NULL) {                    // 检查内存分配是否成功
		fprintf(stderr, "sort table malloc failed!\n");  // 分配失败则打印错误信息到标准错误输出
		return NULL;                        // 返回NULL表示失败
	}
	table->length = n;                      // 设置排序表的长度为n
	table->data = (Element *) malloc(sizeof(Element) * n);  // 为Element数组分配n个元素的内存空间
	if (table->data == NULL) {              // 检查内存分配是否成功
		fprintf(stderr, "element malloc failed!\n");  // 分配失败则打印错误信息
		free(table);                         // 释放之前分配的SortTable内存
		return NULL;                        // 返回NULL表示失败
	}
	srand(time(NULL) + 1);                  // 用当前时间+1初始化随机数种子，+1是为了避免与其他生成器冲突
	for (int i = 0; i < n; ++i) {           // 循环n次，生成n个随机数
		table->data[i].key = (rand() % (high - low + 1)) + low;  // 生成[low, high]范围内的随机整数并赋值给key
		table->data[i].data = NULL;         // 将Element的data指针设置为NULL
	}
	return table;                           // 返回生成的排序表指针
}

/* 产生n个随机交换swapTimes次的有序顺序表 */
SortTable *generateLinearArray(int n, int swapTimes) {
	SortTable *table = (SortTable *)malloc(sizeof(SortTable));  // 为SortTable结构体分配内存
	if (table == NULL) {                    // 检查内存分配是否成功
		fprintf(stderr, "sort table malloc failed!\n");  // 分配失败则打印错误信息
		return NULL;                        // 返回NULL表示失败
	}
	table->data = (Element *)malloc(sizeof(Element) * n);  // 为Element数组分配n个元素的内存空间
	if (table->data == NULL) {              // 检查内存分配是否成功
		fprintf(stderr, "data malloc failed!\n");  // 分配失败则打印错误信息
		free(table);                         // 释放之前分配的SortTable内存
		return NULL;                        // 返回NULL表示失败
	}
	table->length = n;                      // 设置排序表的长度为n
	for (int i = 0; i < n; ++i) {           // 循环n次，生成有序序列
		table->data[i].key = i;             // 设置key为i（0,1,2,...,n-1）
		table->data[i].data = NULL;         // 将Element的data指针设置为NULL
	}
	// 在已经有序的排序表中，随机交换swapTimes次
	srand(time(NULL) + 2);                  // 用当前时间+2初始化随机数种子，+2是为了避免与其他生成器冲突
	for (int i = 0; i < swapTimes; ++i) {   // 循环swapTimes次
		int pos1 = rand() % n;              // 生成[0, n-1]范围内的随机位置pos1
		int pos2 = rand() % n;              // 生成[0, n-1]范围内的随机位置pos2
		swapElement(&table->data[pos1], &table->data[pos2]);  // 交换pos1和pos2位置的元素
	}
	return table;                           // 返回生成的排序表指针
}

/* 拷贝一个排序表，使用同样的数据进行不同排序算法的测试 */
SortTable *copySortTable(SortTable *old) {
	SortTable *table = (SortTable *) malloc(sizeof(SortTable));  // 为新的SortTable结构体分配内存
	table->length = old->length;            // 复制排序表的长度
	table->data = malloc(sizeof(Element) * old->length);  // 为Element数组分配与原表相同大小的内存空间
	for (int i = 0; i < old->length; ++i) { // 循环复制每个元素
		table->data[i].key = old->data[i].key;      // 复制key值
		table->data[i].data = old->data[i].data;    // 复制data指针（注意：这里只复制了指针，没有深拷贝数据）
	}
	return table;                           // 返回拷贝的排序表指针
}

/* 释放table */
void releaseSortTable(SortTable *table) {
	if (table) {                            // 检查table指针是否非空
		if (table->data) {                  // 检查table->data指针是否非空
			free(table->data);              // 释放Element数组的内存
		}
		free(table);                        // 释放SortTable结构体的内存
	}
}

// 检查排序表里的数据，是否是从小到大排序（静态函数，只在本文件中可见）
static enum sortStatus checkData(SortTable *table) {
	for (int i = 0; i < table->length - 1; ++i) {  // 遍历排序表中的元素（除了最后一个）
		if (table->data[i].key > table->data[i + 1].key) {  // 如果前一个元素大于后一个元素
			printf("Check Sort Data Failed: %d : %d\n", table->data[i].key, table->data[i + 1].key);  // 打印错误信息
			return failed;                // 返回失败状态
		}
	}
	return success;                       // 所有元素有序，返回成功状态
}

/* 测试sortName的排序算法，算法通过sort传递函数名，数据以table传入 */
void testSort(const char *sortName, sortHandler sort, SortTable *table) {
	clock_t start = clock();               // 记录排序开始前的时钟周期数
	sort(table);                           // 调用排序函数对table进行排序
	clock_t end = clock();                 // 记录排序结束后的时钟周期数
	if (checkData(table) == failed) {      // 检查排序结果是否正确
		printf("%s failed!\n", sortName);  // 排序失败则打印算法名和失败信息
		return;                            // 直接返回
	}
	// 排序成功则打印算法名和耗时（秒为单位）
	printf("%s cost time: %fs.\n", sortName, (double) (end - start) / CLOCKS_PER_SEC);
}