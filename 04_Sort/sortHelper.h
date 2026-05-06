#ifndef DATASTRUCT2_SORTHELPER_H
#define DATASTRUCT2_SORTHELPER_H
typedef int keyType;
typedef struct {
    keyType key;		// 查找表中每个数据元素的关键值
    void *data;			// 存储与key相关的附加信息
}Element;

//表头
typedef struct {
    Element *data;		// 存放查找表中数据元素的首地址
    int length;			// 查找表的元素个数
}SortTable;


/*
SortTable (排序表容器)
│
├── length: 5
└── data: ──→ [Element数组]
              ├── [0]: {key: 42, data: ──→ [附加数据1]}
              ├── [1]: {key: 17, data: ──→ [附加数据2]}
              ├── [2]: {key: 89, data: ──→ [附加数据3]}
              ├── [3]: {key: 5,  data: ──→ [附加数据4]}
              └── [4]: {key: 23, data: ──→ [附加数据5]}
 */
enum sortStatus{success, failed};

void swapElement(Element *a, Element *b);					// 交换元素a和元素b
SortTable *generateRandomArray(int n, int low, int high);	// 产生随机数范围[low,high]
SortTable *generateLinearArray(int n, int swapTimes);		// 参数顺序空间，随机交换swapTimes次
SortTable *copySortTable(SortTable *old);					// 拷贝和old一样值的排序表
void releaseSortTable(SortTable *table);
// 排序算法函数的别名
typedef void (*sortHandler)(SortTable *);
// 测试sortName的排序算法
void testSort(const char *sortName, sortHandler sort, SortTable *table);
#endif //DATASTRUCT2_SORTHELPER_H

