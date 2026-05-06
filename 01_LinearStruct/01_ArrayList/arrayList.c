#include "arrayList.h"
#include "arrayList.h"
#include <stdlib.h>
#include<stdio.h>
//vector的实现
//扩容接口,static表明只在本文件有效
static int enlarge(ArrayList *table) {
    //申请一个原空间两倍大小的空间
    element_t *temp=(element_t*)malloc(sizeof(element_t)*(table->capacity*2));
    if (temp==NULL) {//判断是否申请成功
        return -1;
    }
    //申请成功后copy原空间的内容,原空间[0,len)拷贝到新空间
    for (int i=0;i<table->len;i++) {
        temp[i]=table->data[i];
    }
    //释放原空间,将原来的*data指向新开辟的空间,在更新表头
    table->capacity=table->capacity*2;
    free(table->data);
    table->data=temp;
    printf("enlarge success!\n");
    return 0;
}
void initArrayList(ArrayList *table,int num) {
    table->data = (element_t*)malloc(num*sizeof(element_t));//创建堆空间
    if (table->data == NULL) {//判断是否申请成功
        table->capacity=0;
        return;
    }
    table->capacity = num;//确定容量,超过要扩容
    table->len=0;//确定索引
}
ArrayList * createArrayList(int num) {
    ArrayList *table=(ArrayList*)malloc(sizeof(ArrayList));
    if (table==NULL) {//申请失败
        return NULL;
    }
    initArrayList(table,num);
    return table;
}
void deleteArrayList(ArrayList *table) {
    if (table->data) {
        free(table->data);//*data是指向这块的指针
        table->data = NULL;
    }
    table->capacity = 0;
    table->len = 0;
}void releaseArrayList(ArrayList *table) {
    if (table) {
        // free(table->data);//如果只free掉table,只是把表头free了
        deleteArrayList(table);
        free(table);
    }
}
void push_backArrayList(ArrayList *table, element_t val) {//尾插法
 //判断是否溢出,如果溢出,扩容
    if (table->len>=table->capacity) {
       if (enlarge(table)!=0) {//扩容失败,0!=0->0,不会进入if,其他!=0->1,进入if
           printf("push back fail\n");
           return;
       }
    }
    table->data[table->len] = val;
    ++table->len;//++写后面也可以,但会产生临时值,降低效率
}
void showArrayList(const ArrayList *table) {
    for (int i=0;i<table->len;i++) {
        printf("%d\t",table->data[i]);
    }
    printf("\n");
}
void insertArrayList(ArrayList *table, int pos, element_t val) {
    //判断插入位置是否有效[0,len]
    if (pos<0||pos>table->len) {
        printf("pos error\n");
        return;
    }
    //判断是否需要扩容
    if (table->len>=table->capacity && enlarge(table)) {//扩容失败
        return;
    }
    //把原来的[pos,len-1]搬移到[pos+1,len],i表示要搬移的数据,搬移到i+1
    for (int i=table->len;i>=pos;i--) {//从后往前,每个位置向后移
        table->data[i]=table->data[i-1];
    }
    //放入新元素
    table->data[pos]=val;
    ++table->len;
}
void deleteValueArrayList(ArrayList *table, element_t val) {
    //先把val的位置找到
    int pos=findArrayList(table,val);
    if (pos==-1) {
        printf("not found\n");
        return;
    }
    //将[pos+1,len)区间的数据搬移到[pos,len-1)
    for (int i=pos+1;i<table->len;i++) {//从前往后,每个位置向前移
        table->data[i-1]=table->data[i];
    }
    //更新len,len有数据，但当作没有，再插入的时候进行覆盖
    --table->len;
}
int findArrayList(const ArrayList *table, element_t val) {
    for (int i=0;i<table->len;i++) {
        if (table->data[i]==val) {
            return i;
        }
    }
    return -1;//未找到该元素
}


