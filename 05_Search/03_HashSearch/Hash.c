#include <stdio.h>
#include <string.h>

#define MAX_NODES 200000  // 预先分配的最大节点数（插入次数）
#define MOD 100003        // 桶大小（质数）

typedef struct {
    int key;
    int value;
    int next;   // 指向下一个节点在 nodes 数组中的下标，-1 表示空
} HashNode;

HashNode nodes[MAX_NODES];
int head[MOD];      // 每个桶的链表头下标，-1 为空
int node_cnt;       // 当前已使用的节点数

void hashmap_init() {
    memset(head, -1, sizeof(head));
    node_cnt = 0;
}

/* 查找 key，返回 value 的指针，未找到返回 NULL */
int *hashmap_find(int key) {
    int h = (unsigned int)key % MOD;
    for (int i = head[h]; i != -1; i = nodes[i].next) {
        if (nodes[i].key == key)
            return &nodes[i].value;
    }
    return NULL;
}

/* 插入/更新 */
void hashmap_insert(int key, int value) {
    int *p = hashmap_find(key);
    if (p) {
        *p = value;
        return;
    }
    int h = (unsigned int)key % MOD;
    // 头插法
    nodes[node_cnt].key = key;
    nodes[node_cnt].value = value;
    nodes[node_cnt].next = head[h];
    head[h] = node_cnt++;
}

int main() {
    hashmap_init();
    hashmap_insert(5, 10);
    hashmap_insert(5, 99);       // 更新
    int *v = hashmap_find(5);
    if (v) printf("%d\n", *v);   // 输出 99
    return 0;
}

/*竞赛板子
const int MOD = 100003;  // 质数，大于最大插入数
const int MAXN = 200005; // 最大节点数
int head[MOD], nxt[MAXN], keys[MAXN], vals[MAXN], tot;
void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}
// 查找：返回 value 指针，找不到返回 nullptr
int* find(int key) {
    int h = (unsigned)key % MOD;
    for (int i = head[h]; i != -1; i = nxt[i])
        if (keys[i] == key) return &vals[i];
    return nullptr;
}

// 插入/更新
void insert(int key, int val) {
    int *p = find(key);
    if (p) { *p = val; return; }
    int h = (unsigned)key % MOD;
    keys[tot] = key;
    vals[tot] = val;
    nxt[tot] = head[h];
    head[h] = tot++;
}
 */