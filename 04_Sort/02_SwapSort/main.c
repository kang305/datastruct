#include "bubbleSort.h"
#include "quickSort.h"

void test01() {
    int n = 10000;
    SortTable *table1 = generateRandomArray(n, 0, n + 2000);
    SortTable *table2 = copySortTable(table1);
    SortTable *table3 = copySortTable(table1);

    testSort("Bubble SortV1", bubbleSortV1, table1);
    testSort("Bubble SortV2", bubbleSortV2, table2);
    testSort("Bubble SortV3", m_bubbleSortV3, table3);

    releaseSortTable(table1);
    releaseSortTable(table2);
    releaseSortTable(table3);
}

void test02() {
    int n = 100000;
    SortTable *table1 = generateRandomArray(n, 0, n + 2000);
    SortTable *table2 = copySortTable(table1);
    SortTable *table3 = copySortTable(table1);

    // testSort("quick SortV1", bubbleSortV3, table1);
    testSort("quick SortV1", quickSortV1, table2);
    testSort("quick SortV2", quickSortV2, table3);

    releaseSortTable(table1);
    releaseSortTable(table2);
    releaseSortTable(table3);
}

int main() {
    test01();
test02();
    return 0;
}