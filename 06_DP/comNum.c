#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int combine01(int n) {
    if (n<0) {
        return 0;
    }
    if (n==0||n==1) {
        return 1;
    }
    return combine01(n-1) + combine01(n-3)+combine01(n-5);
}

/*记忆表*/
static int solve(int n,int *mem) {
    if (n<0) {
        return 0;
    }
    if (n==0||n==1) {
        return 1;
    }
    if (mem[n]==-1) {
        mem[n]=solve(n-1,mem)+solve(n-5,mem)+solve(n-3,mem);
    }
    return mem[n];
}

int combine02(int n) {
    int res = 0;
    int *mem = (int*)malloc(sizeof(int)*(n+1));
    for (int i=0; i<=n; i++) {
        mem[i] = -1;
    }
    res=solve(n,mem);
    free(mem);
    return res;
}

/*dp*/
int combine03(int n) {
    int *mem = (int*)malloc(sizeof(int)*(n+1));
    mem[0]=1;
    mem[1]=1;
    mem[2]=1;
    mem[3]=2;
    mem[4]=3;
    mem[5]=5;
    for (int i=5; i<=n; i++) {
        mem[i]=mem[i-1]+mem[i-3]+mem[i-5];
    }
    int res=mem[n];
    free(mem);
    return res;
}

int main() {
    int x;
    scanf("%d",&x);
    int n1=combine01(x);
    int n2=combine02(x);
    int n3=combine03(x);
    printf("%d\n",n1);
    printf("%d\n",n2);
    printf("%d\n",n3);
    return 0;
}