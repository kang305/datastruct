#include "LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
/*链式栈*/
void initLinkStack(LinkStack *stack) {
    stack->count=0;
    stack->top=NULL;
}

int pushLinkStack(LinkStack *stack, element_t e) {//插入的节点必须在stack->top前面,即new_node->next=stack->top,否则会因为指针移动丢失前面节点的链接
    StackNode *new_node;
    new_node=(StackNode*)malloc(sizeof(StackNode));
    if (new_node==NULL) {
        return 0;
    }
    new_node->data=e;
    new_node->next=stack->top;//可以理解为头插法,stack->top就是此时的栈顶元素
    stack->top=new_node;//top指针就是栈顶元素,插入后要更新为新插入的节点
    ++stack->count;//节点数加一
    return 1;
}

int popLinkStack(LinkStack *stack, element_t *e) {//e用来备份删除数据的
    if (stack->count==0) {//空栈
        printf("stack is empty\n");
        return 0;
    }
    *e=stack->top->data;//备份原栈顶的数据
    StackNode *temp=stack->top;//备份原栈顶
    stack->top=temp->next;//让top后移
    free(temp);
    --stack->count;
}

int gettopLinkStack(const LinkStack *stack) {
    return stack->top->data;
}
