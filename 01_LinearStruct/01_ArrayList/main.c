#include <stdio.h>
#include"arrayList.h"
void testtable(ArrayList *table) {
    for (int i=0;i<5;i++) {
        push_backArrayList(table,i+100);
    }
    showArrayList(table);
    push_backArrayList(table,1000);
    showArrayList(table);
    insertArrayList(table,1,1209);
    showArrayList(table);
    insertArrayList(table,2,418);
    showArrayList(table);
    deleteValueArrayList(table,102);
    showArrayList(table);
}
void test01() {
    ArrayList table;
    initArrayList(&table, 5);
    testtable(&table);
    deleteArrayList(&table);
}

void test02() {
    ArrayList *table= createArrayList(5);
    testtable(table);
    releaseArrayList(table);
}
int main() {
    test01();
    printf("====================================\n");
    test02();
    return 0;
}