#ifndef DATASTRUCT2_LINKSTACK_H
#define DATASTRUCT2_LINKSTACK_H
typedef int element_t;
/*链式栈的节点节点结构*/
typedef struct stack_node{
    element_t data;
    struct stack_node* next;
}StackNode;
/*头节点*/
typedef struct {
    StackNode* top;
    int count;
}LinkStack;

void initLinkStack(LinkStack* stack);
int pushLinkStack(LinkStack* stack, element_t e);
int popLinkStack(LinkStack* stack, element_t *e);
int gettopLinkStack(const LinkStack* stack);

#endif //DATASTRUCT2_LINKSTACK_H