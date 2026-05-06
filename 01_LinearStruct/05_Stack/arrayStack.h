#ifndef DATASTRUCT2_ARRAYSTACK_H
#define DATASTRUCT2_ARRAYSTACK_H
typedef int element_t;
#define MaxStackSize 5
typedef struct {
    element_t data[MaxStackSize];//存放元素的空间
    int top;//栈顶指针作为索引
}ArrayStack;
/*满递增栈,顺序栈*/
void initArrayStack(ArrayStack *stack);

int isEmptyArrayStack(const ArrayStack *stack);//判断是否为空栈
int isFullArrayStack(const ArrayStack *stack);//判断是否已满

void pushArrayStack(ArrayStack *stack,element_t val);//压栈

void popArrayStack(ArrayStack *stack);//出栈只是维护栈的空间行为,出栈的结果忽略
element_t getTopArrayStack(ArrayStack *stack);//查看栈顶元素
/*空递增栈*/
void initArrayStackem(ArrayStack *stack);

int isEmptyArrayStackem(const ArrayStack *stack);
int isFullArrayStackem(const ArrayStack *stack);

void pushArrayStackem(ArrayStack *stack,element_t val);

void popArrayStackem(ArrayStack *stack);
element_t getTopArrayStackem(ArrayStack *stack);

#endif //DATASTRUCT2_ARRAYSTACK_H