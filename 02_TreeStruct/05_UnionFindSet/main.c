#include <stdio.h>
#include "quickFindSet.h"
#include "quickUnionSet.h"
void test01() {
    int n = 9;
    QuickFindSet *QFSet = createQuickFindSet(n);
    element_t data[9];
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        data[i] = i;
    }
    initQuickFindSet(QFSet, data, n);

    unionQF(QFSet, 3, 4);
    unionQF(QFSet, 8, 0);
    unionQF(QFSet, 2, 3);
    unionQF(QFSet, 5, 6);
    isSameQF(QFSet, 0, 2) ? printf("Yes\n") : printf("No\n");
    isSameQF(QFSet, 2, 4) ? printf("Yes\n") : printf("No\n");
    unionQF(QFSet, 5, 1);
    unionQF(QFSet, 7, 3);
    unionQF(QFSet, 1, 6);
    unionQF(QFSet, 4, 8);
    isSameQF(QFSet, 0, 2) ? printf("Yes\n") : printf("No\n");
    isSameQF(QFSet, 2, 4) ? printf("Yes\n") : printf("No\n");

    releaseQuickFindSet(QFSet);
}
void test02() {
    int n = 9;
    QuickUnionSet *QUSet = createQuickUnionSet(n);
    element_t data[9];
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        data[i] = i;
    }
    initQuickUnionSet(QUSet, data, n);

    unionQU(QUSet, 3, 4);
    unionQU(QUSet, 8, 0);
    unionQU(QUSet, 2, 3);
    unionQU(QUSet, 5, 6);
    isSameQU(QUSet, 0, 2) ? printf("Yes\n") : printf("No\n");
    isSameQU(QUSet, 2, 4) ? printf("Yes\n") : printf("No\n");
    unionQU(QUSet, 5, 1);
    unionQU(QUSet, 7, 3);
    unionQU(QUSet, 1, 6);
    unionQU(QUSet, 4, 8);
    isSameQU(QUSet, 0, 2) ? printf("Yes\n") : printf("No\n");
    isSameQU(QUSet, 2, 4) ? printf("Yes\n") : printf("No\n");

    releaseQuickUnionSet(QUSet);
}
void test03() {
    int n = 9;
    QuickUnionSet *QUSet = createQuickUnionSet(n);
    element_t data[9];
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        data[i] = i;
    }
    initQuickUnionSet(QUSet, data, n);

    unionQU2(QUSet, 3, 4);
    unionQU2(QUSet, 8, 0);
    unionQU2(QUSet, 2, 3);
    unionQU2(QUSet, 5, 6);
    isSameQU(QUSet, 0, 2) ? printf("Yes\n") : printf("No\n");
    isSameQU(QUSet, 2, 4) ? printf("Yes\n") : printf("No\n");
    unionQU2(QUSet, 5, 1);
    unionQU2(QUSet, 7, 3);
    unionQU2(QUSet, 1, 6);
    unionQU2(QUSet, 4, 8);
    isSameQU(QUSet, 0, 2) ? printf("Yes\n") : printf("No\n");
    isSameQU(QUSet, 2, 4) ? printf("Yes\n") : printf("No\n");

    releaseQuickUnionSet(QUSet);
}

int main() {
   test01();
   test02();
   test03();
    return 0;
}