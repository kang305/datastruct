#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int fib01(unsigned int n) {//纯递归
   if (n==0) {
       return 0;
   }
    if (n==1) {
        return 1;
    }
   return  fib01(n-1)+fib01(n-2);
}
void test01() {
    clock_t start = clock();
    unsigned int x = fib01(35);
    clock_t end = clock();
    printf("cost time:%fs ,fib01=%u\n",(double)(end-start)/CLOCKS_PER_SEC,x);
}

/*利用记忆搜索表*/
//mem1[i]记忆了第i个斐波那契数列的值
static unsigned int *mem1;
unsigned int fib02(unsigned int n) {
    if (n==0) {
        return 0;
    }
    if (n==1) {
        return 1;
    }
    if (mem1[n]==-1) {
        mem1[n] = fib02(n-1)+fib02(n-2);
    }
    return  mem1[n];
}

void test02() {
   int n=1000;
   mem1 = (unsigned int *)malloc((n+1)*sizeof(unsigned int));
    //初始化这个表里,存储一个以后算法中永远不会出现的状态
    for(int i=0;i<=n;i++) {
        mem1[i] = -1;
    }
    clock_t start = clock();
    unsigned int x = fib02(35);
    clock_t end = clock();
    printf("cost time:%fs ,fib02=%u\n",(double)(end-start)/CLOCKS_PER_SEC,x);
    free(mem1);
}

/*利用动态规划表*/
unsigned int fib03(unsigned int n) {
   unsigned int *mem = malloc((n+1)*sizeof(unsigned int));
    mem[0] = 0;
    mem[1] = 1;
    for(int i=2;i<=n;i++) {
        mem[i] = mem[i-1]+mem[i-2];
    }
    unsigned int result = mem[n];
    free(mem);
    return result;
}
void test03() {
    clock_t start = clock();
    unsigned int x = fib03(35);
    clock_t end = clock();
    printf("cost time:%fs ,fib03=%u\n",(double)(end-start)/CLOCKS_PER_SEC,x);
}
int main() {
    test01();
    test02();
    test03();
}