#include "arrayStack.h"
#include<stdio.h>
#include<stdlib.h>
/*满递增栈,顺序栈*/
void initArrayStack(ArrayStack *stack) {
    stack->top = -1;//满栈的指针指向有数据的空间,初始时让其指向-1,后面先++
}

int isEmptyArrayStack(const ArrayStack *stack) {
    return (stack->top == -1);//初始top是-1,当top=-1代表空
}

int isFullArrayStack(const ArrayStack *stack) {
    return (stack->top==MaxStackSize-1);//从零开始计数[0,MaxStackSize-1]
}

void pushArrayStack(ArrayStack *stack, element_t val) {
    if (isFullArrayStack(stack)) {
        printf("Stack full\n");
        return;
    }
    stack->data[++stack->top] = val;//因为满栈top此时指向的地方会存数据,所以先++top
}

void popArrayStack(ArrayStack *stack) {
    if (isEmptyArrayStack(stack)) {
        printf("Stack empty\n");
        return;
    }
    stack->top--;
}

element_t getTopArrayStack(ArrayStack *stack) {
    return stack->data[stack->top];
}
/*空递增栈*/
void initArrayStackem(ArrayStack *stack) {
    stack->top = 0;
}

int isEmptyArrayStackem(const ArrayStack *stack) {
    return (stack->top == 0);
}

int isFullArrayStackem(const ArrayStack *stack) {
    return(stack->top==MaxStackSize-1);
}

void pushArrayStackem(ArrayStack *stack, element_t val) {
    if (isFullArrayStackem(stack)) {//最后的一个空间空着但top依旧指这
        printf("Stack full\n");
        return;
    }
    stack->data[stack->top] = val;
    stack->top++;
}

void popArrayStackem(ArrayStack *stack) {
    if (isEmptyArrayStackem(stack)) {
        printf("stack empty");
        return;
    }
    stack->top--;
}

element_t getTopArrayStackem(ArrayStack *stack) {
    if (isEmptyArrayStackem(stack)) {
        printf("stack empty\n");
        return -1; // 栈空时返回无效值，可根据需求调整
    }
    return stack->data[stack->top - 1];

}


