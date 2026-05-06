
#include<stdlib.h>
#include "findStr.h"

int strAssign(StrType *str, char *ch) {
    if (str->str) {  //str已经指向了数据,释放后重新再通过ch来赋值
        free(str->str);
    }
    //求ch长度
    int len=0;
    while (ch[len]) {
        len++;
    }
    if (len==0) {
        str->str=NULL;
        str->length=0;
    }else {
        str->str=(char*)malloc(sizeof(char)*(len+2)); //把0号位置空出来,把\0也放入空间内

        for (int i=0;i<=len;i++) {  //包含ch指向空间的\0位置
            str->str[i+1]=ch[i];
        }
        str->length=len;
    }
  return 1;
}

void releaseStr(StrType *str) {
    if (str->str!=NULL) {
        free(str->str);
    }
    str->length=0;
    str->str=NULL;
}

int index_simple(const StrType *str, const StrType *subStr) {
    int i = 1;          // 主串的当前位置（从1开始）
    int j = 1;          // 子串的当前位置
    int k = i;          // 记录本次匹配的起始位置

    //循环条件：两串都未扫描完
    while (i <= str->length && j <= subStr->length) {
        //当前位置字符匹配成功
        if (str->str[i] == subStr->str[j]) {
            i++;        //主串指针后移
            j++;        //子串指针后移
        } else {
            k++;        //匹配失败，起始位置后移一位
            j = 1;      //子串从头开始
            i = k;      //主串从新的起始位置开始
        }
    }
    //判断匹配结果
    if (j>subStr->length) {
        return k;       //返回匹配成功的起始位置（从1开始计数）
    } else{
        return 0;       //匹配失败，返回0
    }
}

/*getNext()函数的核心思想：
1. 用模式串自己匹配自己
2. i 是后缀的末尾,j 是前缀的末尾
3. 当 P[i] == P[j] 时，最长相等前后缀长度增加
4. 当不相等时，利用已计算的 next 值回溯*/

// 计算KMP算法中的next数组

//next[j+1]的最大值为next[j]+1
//如果p[j]!=p[ next[j] ],next[j+1]可能的次大值为next[ next[j] ]+1,以此类推
void getNext(const StrType *subStr, int next[]) {
    int i=1;      //后缀末尾位置
    int j=0;      //前缀末尾位置（也代表当前匹配长度）
    next[1]=0;    //第一个字符的next值为0

    //计算每个位置的next值
    while (i < subStr->length) {  //i从1开始，计算到length-1(最后一个可以不用算)
        if (j == 0 || subStr->str[i] == subStr->str[j]) {
            i++;            //指针后移
            j++;            //匹配长度增加
            next[i] = j;    //记录next值
        } else {
            j = next[j];    //匹配失败，回溯到前一个next值位置
        }
    }
}
//求next数组的改进方法
void getNext_improve(const StrType *subStr, int nextval[]) {
    int i=1;
    nextval[1]=0;
    int j=0;
    while (i < subStr->length) {
        if (j == 0 || subStr->str[i] == subStr->str[j]) {
            i++;
            j++;
            if (subStr->str[i] != subStr->str[j]) {
                nextval[i] = j;
            }else {
                nextval[i] = nextval[j];
            }
        }else {
            j=nextval[j];
        }
    }
}
// KMP字符串匹配算法
int indexKMP(const StrType *str, const StrType *subStr, const int *next) {
    int i = 1;      //主串指针
    int j = 1;      //子串指针

    // 遍历主串和子串
    while (i <= str->length && j <= subStr->length) {
        //j==0表示子串需要从头开始匹配
        //当前位置字符匹配成功
        if (j==0||str->str[i]==subStr->str[j]) {//子串的0号位未存放字符,j==0意味着str[i]已经不可能与substr[]前面任何一个子串匹配,跳过i
            ++i;    //主串指针后移
            ++j;    //子串指针后移
        } else {
            j=next[j];  //利用next数组跳过不必要的比较
        }
    }

    // 判断匹配结果
    if (j>subStr->length) {
        return i-subStr->length;  // 返回匹配成功的起始位置
    }
    return 0;  // 匹配失败
}
