#include <stdio.h>
#include "miniHeap.h"
#include "heapSort.h"

void test01() {
    int data[] = {9, 3, 7, 6, 5, 1, 10};
    int n = 20;
    MiniHeap *mini_heap = createMiniHeap(n);
    if (mini_heap == NULL) {
        return;
    }
    for (int i = 0; i < sizeof(data)/sizeof(data[0]); ++i) {
        insertMiniHeap(mini_heap, data[i]);
    }
    printf("array: ");
    for (int i = 0; i < sizeof(data)/sizeof(data[0]); ++i) {
    	printf("\t%d", mini_heap->data[i]);
    }
    printf("\n extra: ");
    for (int i = 0; i < sizeof(data)/sizeof(data[0]); ++i) {
        printf("\t%d", extractMiniHeap(mini_heap));
    }
    releaseMiniHeap(mini_heap);
}

void test02() {
    int n = 10000;
    SortTable *table = generateRandomArray(n, 0, n + 1000);
    testSort("HeapSort: ", MiniHeapSort, table);
    releaseSortTable(table);
}

int main() {
    test01();
     printf("\n");
    test02();

    return 0;
}
