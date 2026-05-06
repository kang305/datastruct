#ifndef DATASTRUCT2_ARRAYLIST_H
#define DATASTRUCT2_ARRAYLIST_H
//接口声明
#ifndef DATASTRUCT_ARRAYLIST_H
#define DATASTRUCT_ARRAYLIST_H
/*实现顺序表的结构定义*/
typedef int element_t;
typedef struct  {
    element_t* data;  //指向顺序表的数据正文区
    int capacity;     //顺序表数据正文的最大容量,索引不能取到这个值[0,capacity)
    int len;          //数据正文区含有的数据数量,尾插法的索引节点,插入位置(还没插)
}ArrayList;
//顺序链表中，len 指的位置是不是始终指向一个没数据的地方,有时len有数据，但当作没有，再插入的时候进行覆盖
/*顺序表的初始化接口*/
void initArrayList(ArrayList *table,int num);   //初始化一个表,已经有表头,需要初始化正文数据
void deleteArrayList(ArrayList *table);         //清除一个表的正文数据内容

ArrayList *createArrayList(int num);            //创建一个表,包含表头和正文数据
void releaseArrayList(ArrayList *table);        //释放表头和正文区

/*顺序表插入接口,尾插法,任意位置的插入*/
void push_backArrayList(ArrayList *table,element_t val);//尾插法
void insertArrayList(ArrayList* table,int pos,element_t val);//任意位置插入

/*顺序表的遍历显示接口*/
void showArrayList(const ArrayList *table);      //加const表示只读

/*顺序表查找元素接口,返回索引号*/
int findArrayList(const ArrayList *table,element_t val);

/*顺序表删除操作接口,删除某个值*/
void deleteValueArrayList(ArrayList *table,element_t val);
#endif //DATASTRUCT_ARRAYLIST_H
#endif //DATASTRUCT2_ARRAYLIST_H