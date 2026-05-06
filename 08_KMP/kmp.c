#include <stdio.h>
#include <stdlib.h>

#include "findStr.h"

void test01(const StrType *str, const StrType *subStr) {
    int res = index_simple(str, subStr);
    printf("simple find index: %d\n", res);
}

void test02(const StrType *str, const StrType *pattern) {
    int *next = malloc(sizeof(int) * (pattern->length + 1));
    getNext_improve(pattern, next);
    printf("KMP find index:%d\n", indexKMP(str, pattern, next));
    free(next);
}

int main() {
    StrType str;
    StrType subStr;
    str.str = NULL;
    subStr.str = NULL;
    strAssign(&str, "ABCDABCABCABABCABCDA");
    strAssign(&subStr, "ABCABCD");

    test02(&str, &subStr);

    return 0;
}