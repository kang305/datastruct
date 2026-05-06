#include "mergeSort.h"

int main() {
    int n = 1000000;
    SortTable *table = generateRandomArray(n, 0, n + 3000);
    testSort("MergeSort", mergeSort, table);
    releaseSortTable(table);
    return 0;
}

