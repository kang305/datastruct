#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int element_t; // 定义元素类型为int，方便后续更改数据类型

//哈希查找
/* 哈希表节点定义 */
typedef struct HashNode {
    element_t data;          // 存储数据
    struct HashNode* next;   // 指向下一个节点的指针（解决哈希冲突的链地址法）
} hash;

/*哈希表头定义*/
typedef struct {
    hash** array;    // 哈希表数组，每个元素是指向链表头节点的指针
    int length;      // 哈希表长度(数组大小)同时也是哈希的模长
} hashHead;

/* 创建哈希表并初始化 */
hashHead* createHash(const element_t *arr, int n) {
    // 分配哈希表头结构体内存
    hashHead* head = (hashHead*)malloc(sizeof(hashHead));
    // 分配哈希表数组内存，初始化为NULL（calloc会自动清零）
    head->array = (hash**)calloc(n, sizeof(hash*));
    head->length = n;  // 设置哈希表长度

    // 将数组元素插入哈希表
    for (int i = 0; i < n; ++i) {
        int index = arr[i] % n;  // 哈希函数：取模运算
        // 创建新节点
        hash* newNode = (hash*)malloc(sizeof(hash));
        newNode->data = arr[i];
        // 头插法：新节点指向原链表头，然后成为新链表头
        newNode->next = head->array[index];
        head->array[index] = newNode;
    }
    return head;  // 返回哈希表头指针
}

/* 释放哈希表 */
void freeHash(hashHead* head) {
    if(head == NULL) {  //检查
        return;
    }
    // 遍历哈希表所有位置
    for(int i = 0; i < head->length; i++) {
        hash* current = head->array[i];  // 获取链表头
        // 遍历链表释放所有节点
        while(current != NULL) {
            hash* temp = current;       // 保存当前节点
            current = current->next;    // 移动到下一个节点
            free(temp);                 // 释放当前节点
        }
    }
    free(head->array);  // 释放哈希表数组
    free(head);         // 释放哈希表头
}

/*哈希查找函数*/
int hashSearch(hashHead *head, element_t target) {
    if(head == NULL) {  //检查
        return -1;
    }

    int index = target % head->length;  //计算哈希值
    hash* current = head->array[index]; //获取对应链表的头节点

    // 遍历链表查找目标值
    while(current != NULL) {
        if(current->data == target) {
            return target;  //找到目标，返回目标值
        }
        current = current->next;  //移动到下一个节点
    }

    return -1;  //未找到，返回-1
}



//二分查找:需要数据上有序的
/* 1. 半闭半开区间二分查找 [left, right) */
int binarySearch2(const element_t *arr, int n, element_t target) {
    int left = 0;
    int right = n;  // 右边界为n（不包含）
    while (left < right) {  // 左闭右开，所以left==right时循环结束
        int mid = left + (right - left) / 2;  // 计算中间位置，避免溢出
        if (arr[mid] == target) {
            return target;  // 找到目标
        } else if (arr[mid] < target) {
            left = mid + 1;  // 目标在右半部分(left是可取的所以mid更新要加1)
        } else {
            right = mid;     // 目标在左半部分(right取不到不加1)
        }
    }
    return -1;  // 未找到
}

/* 2. 闭区间二分查找 [left, right] */
int binarySearch(element_t *arr, int n, element_t target) {
    int left = 0;
    int right = n - 1;  // 右边界为n-1（包含）
    while (left <= right) {  // 闭区间，left>right时循环结束
        int mid = (right - left) / 2 + left;  // 计算中间位置
        if (arr[mid] == target) {
            return target;  // 找到目标
        } //mid不是目标，处理区间的时候不包含
        else if (arr[mid] > target) {
            right = mid - 1;  // 目标在左半部分
        } else {
            left = mid + 1;   // 目标在右半部分
        }
    }
    return -1;  // 未找到
}

/* 普通顺序查找 */
element_t normalSearch(const element_t *arr, int n, element_t target) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == target) {
            return target;  // 找到目标
        }
    }
    return -1;  // 未找到
}

/* 生成有序数组 */
element_t *generateOrderArray(int n) {
    // 分配n个元素的内存空间
    element_t *arr = (element_t*)malloc(sizeof(element_t) * n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i;  // 生成0到n-1的有序数组
    }
    return arr;
}

int main() {
    int n = 10000;  // 测试数据规模
    element_t *array = generateOrderArray(n);  // 生成有序数组

    // 测试二分查找（使用半闭半开区间版本）
    clock_t start = clock();  // 记录开始时间
    for (int i = 0; i < n; ++i) {
        // 查找每个元素，验证查找结果
        if (i != binarySearch2(array, n, i)) {
            printf("binary search Not find\n");  // 查找失败输出信息
            break;
        }
    }
    clock_t end = clock();  // 记录结束时间
    // 计算并输出二分查找耗时
    printf("Binary search time: %fs\n", (double)(end - start)/CLOCKS_PER_SEC);

    //测试顺序查找
    start = clock();
    for (int i = 0; i < n; ++i) {
        if (i != normalSearch(array, n, i)) {
            printf("normal search Not find\n");
            break;
        }
    }
    end = clock();
    printf("Normal search time: %fs\n", (double)(end - start)/CLOCKS_PER_SEC);

   // 测试哈希查找
    start = clock();
    hashHead* head = createHash(array, n);  // 创建哈希表
    for (int i = 0; i < n; ++i) {
        if (i != hashSearch(head, i)) {
            printf("hash search Not find\n");
            break;
        }
    }
    end = clock();
    printf("Hash  search  time: %fs\n", (double)(end - start)/CLOCKS_PER_SEC);

    // 释放动态分配的内存
    freeHash(head);    //释放哈希表
    free(array);       //释放数组

    return 0;
}