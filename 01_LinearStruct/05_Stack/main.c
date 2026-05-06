#include <stdio.h>
#include"arrayStack.h"
#include"LinkStack.h"
void test01(){
ArrayStack stack;
    initArrayStack(&stack);
    for (int i = 0; i <MaxStackSize; ++i) {
        pushArrayStack(&stack, i+10);
    }
    pushArrayStack(&stack, 1);
    while (!isEmptyArrayStack(&stack)) {
        printf("%d  ", getTopArrayStack(&stack));
        popArrayStack(&stack);
    }
    printf("\n");
    popArrayStack(&stack);
}

void test02() {
    LinkStack stack;
    initLinkStack(&stack);
    for (int i = 0; i <MaxStackSize; ++i) {
        pushLinkStack(&stack, i+10);
    }
    element_t e;
   while (popLinkStack(&stack,&e)) {
       printf("%d  ", e);
   }
    printf("\n");
    popLinkStack(&stack,&e);
}

void test03() {
    ArrayStack stack;
    initArrayStackem(&stack);
    for (int i = 0; i <MaxStackSize; ++i) {
        pushArrayStackem(&stack, i+10);
    }
    pushArrayStackem(&stack, 1);

  while (!isEmptyArrayStackem(&stack)){
    printf("%d  ", getTopArrayStackem(&stack));
    popArrayStackem(&stack);
 }
 printf("\n");
 popArrayStackem(&stack);
}
int main() {
//test01();
//test02();
test03();
    return 0;
}