#include "insertSort.h"

int main() {
    int n = 100;

    SortTable *table1 = generateRandomArray(n, 0, n + 1000);
    // SortTable *table2 = generateLinearArray(n, 10);
    SortTable *table2 = copySortTable(table1);

    testSort("random insertSort: ", insertSortV1, table1);
    // testSort("linear insertSort: ", insertSortV1, table2);
    testSort("shell  insertSort: ", shellSort, table2);

    releaseSortTable(table1);
    releaseSortTable(table2);
    return 0;
}
