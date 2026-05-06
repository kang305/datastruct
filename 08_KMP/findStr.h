#ifndef DATASTRUCT2_FINDSTR_H
#define DATASTRUCT2_FINDSTR_H
typedef struct {
    char *str;
    int length;
}StrType;

int strAssign(StrType *str, char *ch);          // 字符串赋值函数
void releaseStr(StrType *str);                  // 释放字符串内存
int index_simple(const StrType *str, const StrType *subStr);  // 暴力匹配算法
void getNext(const StrType *subStr, int next[]);              // 计算KMP的next数组
int indexKMP(const StrType *str, const StrType *subStr, const int *next);  // KMP匹配算法
void getNext_improve(const StrType *subStr, int nextval[]);
#endif //DATASTRUCT2_FINDSTR_H