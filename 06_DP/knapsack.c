#include<stdio.h>
#include<stdlib.h>

// 定义物品的重量和价值数组，以及背包容量（全局静态变量）
static int wt_goods[]={1,2,3};        // 物品重量
static int val_goods[]={6,10,12};     // 物品价值
static int bag_capacity=5;            // 背包容量

// 辅助函数：返回两个整数中的最大值
static int max(int a,int b) {
    return a>b?a:b;
}

// ==================== 方法1：递归解法（暴力搜索）====================
// 参数：index:当前考虑的物品索引，capacity:当前背包剩余容量
// 返回值：用[0...index]的物品填充容量为capacity的背包的最大价值
static int bestValue01(int index,int capacity) {
    // 边界条件：没有物品可选(index<0)或背包容量不足(capacity<=0)
    if (index<0||capacity<=0) {
        return 0;  // 无法选择物品或装入物品，价值为0
    }
    // 策略1：不选择当前物品index
    // 递归计算只考虑[0...index-1]这些物品填充容量为capacity的背包
    int res=bestValue01(index-1,capacity);

    // 策略2：如果背包能装下当前物品index，则考虑选择它
    if (capacity>=wt_goods[index]) {
        // 选择当前物品：价值=当前物品价值+剩余容量下的最大价值
        // 剩余容量 = capacity-wt_goods[index]，物品范围 = [0...index-1]
        res=max(val_goods[index]+bestValue01(index-1,capacity-wt_goods[index]), res);//index+空出index的最大与完全不算index比较
    }
    // 返回两种策略中的最大值
    return res;
}

// 调用递归解法
int knapsack01() {
    // 初始调用：考虑所有物品[0...2]，初始容量为背包总容量5
    // 注意：索引减1是因为数组从0开始，最大索引是长度-1
    return bestValue01(sizeof(wt_goods)/sizeof(wt_goods[0])-1,bag_capacity);
}

// ==================== 方法2：记忆化搜索（自顶向下）====================
// 参数：data:指向记忆化数组的指针
static int bestValue02(int index,int capacity,void *data) {
    // 将void*指针转换为二维数组指针
    // mem是一个指向二维数组的指针，每行有(bag_capacity+1)个元素
    int (*mem)[bag_capacity+1]=data;

    // 边界条件
    if (index<0||capacity<=0) {
        return 0;
    }

    // 如果已经计算过该子问题，直接返回结果（避免重复计算）
    // 注意：mem[index][capacity]存储的是考虑[0...index]物品，容量为capacity时的最大价值
    if (mem[index][capacity]!=-1) {
        return mem[index][capacity];
    }

    // 计算过程与bestValue01相同，只是会存储结果到mem
    int res=bestValue02(index-1,capacity,data);
    if (capacity>=wt_goods[index]) {
        res=max(res,val_goods[index]+bestValue02(index-1,capacity-wt_goods[index],mem));
    }
    // 存储计算结果到记忆化表
    mem[index][capacity]=res;
    return res;
}

// 调用记忆化搜索解法
int knapsack02() {
    int n=sizeof(val_goods)/sizeof(val_goods[0]);

    // 动态分配记忆化数组：n行 × (bag_capacity+1)列
    // 为什么列数是bag_capacity+1:因为容量范围是0到bag_capacity，共bag_capacity+1种可能
    int (*mem)[bag_capacity+1]=malloc(sizeof(int)*n*(bag_capacity+1));

    // 初始化记忆化数组为-1（表示未计算）
    // 注意：i从0到n-1（遍历所有物品），j从0到bag_capacity（遍历所有容量）
    for (int i=0;i<n;i++) {
        for (int j=0;j<=bag_capacity;j++) {  // j<=bag_capacity，包含容量0
            mem[i][j]=-1;
        }
    }

    // 调用记忆化搜索函数
    // 从最后一个物品(n-1)开始，初始容量为bag_capacity
    int res=bestValue02(n-1, bag_capacity, mem);

    // 释放动态分配的内存
    free(mem);
    return res;
}

// ==================== 方法3：动态规划（自底向上）====================
// 参数：n物品数量,capacity背包容量
int knapsackDP(int n,int capacity) {
    // 动态分配DP表：n行 × (capacity+1)列
    // dp[i][j]表示只考虑前i个物品（索引0到i）放或不放,且容量为j时的最大价值
    int (*dp)[capacity+1]=malloc(sizeof(int)*n*(capacity+1));
    // 初始化第一行（只考虑第一个物品）-->以第一行为基础逐步推导后面的行
    // j从0到capacity（包含容量0）
    for (int j=0;j<=capacity;j++) {
        if (j>=wt_goods[0]) {
            // 如果当前容量j能装下第一个物品，则最大价值为第一个物品的价值
            dp[0][j]=val_goods[0];
        } else {
            // 装不下第一个物品，价值为0
            dp[0][j]=0;
        }
    }
    // 递推填充DP表：i从1到n-1（从第二个物品开始考虑）
    for (int i=1;i<n;i++) {
        // j从0到capacity，遍历所有可能的容量
        for (int j=0;j<=capacity;j++) {
            // 策略1：不选择当前物品i
            // 最大价值等于考虑前i-1个物品，容量为j时的价值
            dp[i][j]=dp[i-1][j];
            // 策略2：如果当前容量j能装下物品i，考虑选择它
            if (j>=wt_goods[i]) {
                // 选择物品i的价值=物品i的价值+dp[i-1][j-wt_goods[i]]
                // 注意：因为每个物品只能选一次，所以是dp[i-1]而不是dp[i]
                //dp[i][j]最后为不选i或选i后的最大值
                dp[i][j]=max(dp[i-1][j], val_goods[i]+dp[i-1][j-wt_goods[i]]);
            }
            // 如果j<wt_goods[i]，无法选择物品i，保持策略1的值
        }
    }
    // 最终结果：考虑所有n个物品，容量为capacity时的最大价值
    int res=dp[n-1][capacity];
    free(dp);
    return res;
}

int main() {
    // 测试记忆化搜索解法
    int res=knapsack02();
    // 测试动态规划解法
    int result = knapsackDP(sizeof(wt_goods)/sizeof(wt_goods[0]), bag_capacity);
    printf("%d",res);
    printf("\n%d",result);
    return 0;
}