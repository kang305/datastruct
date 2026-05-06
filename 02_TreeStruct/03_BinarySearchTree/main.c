#include"BSTree.h"
#include<stdio.h>
#include<time.h>
#include <stdlib.h>


void test01() {
    element_t data[]={55,33,45,100,22,80,8,130,120,121};
    BSTree *tree = createBSTree();

    for (int i = 0; i<sizeof(data)/sizeof(data[0]); i++) {
        insertBSTreeV1(tree, data[i]);
    }
    inOrderBSTree(tree);
    // preOrderBSTree(tree);
    // PostOrderBSTree(tree);
    printf("\n");
    printf("tree height:%d",heightBSTree(tree));
    printf("\n");
    BSNode* result = searchBSTree(tree, 230);
    if (result) {
        printf("search %d success\n",result->data);
    }else {
        printf("search failure\n");
    }
    deleteBSTreeV1(tree, 55);
    inOrderBSTree(tree);
    releaseBSTree(tree);
}

void test02() {
    int n = 10000;
    srand(time(NULL) + 1);
    element_t *data = malloc(sizeof(element_t) * n);

    for (int i = 0; i < n; ++i) {
        data[i] = rand() % (n + 1000) + 1;
    }

    int cnt = 50000; // 做了cnt次实验
    clock_t start = clock();
    for (int i = 0; i < cnt; ++i) {
        // 每次实验都从data里找一个不存在的值
        for (int j = 0; j < n; ++j) {
            if (data[j] == n + 50000) {
                printf("find error!\n");
            }
        }
    }
    clock_t end = clock();
    printf("linear find cost %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("==============================\n");
    BSTree *tree = createBSTree();
    for (int i = 0; i < n; ++i) {
        insertBSTreeV1(tree, data[i]);
    }
    start = clock();
    // 做了cnt次实验
    for (int i = 0; i < cnt; ++i) {
        // 每次实验都从二叉搜索树中找一个不存在的值
        BSNode *res = searchBSTree(tree, n + 5000);
        if (res != NULL) {
            printf("BSTree find error!\n");
        }
    }

    end = clock();
    printf("BSTree find cost %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    releaseBSTree(tree);
    free(data);
}

void test03() {
    element_t data[] = {55, 33, 45, 100, 22, 80, 8, 130, 120, 121, 122};
    BSTree *tree = createBSTree();

    for (int i = 0; i < sizeof(data)/sizeof(data[0]); ++i) {
        insertBSTreeV2(tree, data[i]);
    }
    inOrderBSTree(tree);
    printf("tree height: %d\n", heightBSTree(tree));

    BSNode *result = searchBSTree(tree, 100);
    if (result) {
        printf("search %d success!\n", result->data);
    } else {
        printf("search failed!\n");
    }
    deleteBSTreeV2(tree, 8);
    inOrderBSTree(tree);
    releaseBSTree(tree);
}
int main() {
    //test01();
    // test02();
     test03();
    return 0;
}