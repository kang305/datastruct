#include "HuffmanTree.h"
#include <stdlib.h>
#include <string.h>
//在已有的权值中找最小的两个
static void selectTwoMin(HuffmanTree tree,int n,int *s1,int *s2) {//传的是s1和s2的地址出函数后就是更改后的min
    *s1=*s2=0;//先让最小值都指向0号节点
    for(int i=1;i<=n;i++) {
        if (tree[i].parent==0) {//没父节点才需要进行操作
            if (*s1==0) {
                *s1=i;
            }
            else if (*s2==0) {
                *s2=i;
                if (tree[*s1].weight>tree[*s2].weight) {//当s1存的权值>s2的权值,交换s1和s2,s1存的权值<s2的权值,即s1<s2<其他
                    int t=*s1;
                    *s1=*s2;
                    *s2=t;
                }
            }
            else {
                //比较权值大小,更新最小的2个节点下标
                if (tree[i].weight<tree[*s1].weight) {
                    *s2=*s1;//先用s2存下s1
                    *s1=i;//s1更新为最小的
                }
                else if (tree[i].weight<tree[*s2].weight) {
                    *s2=i;//s2更新为次小的
                }
            }
        }
    }
}

HuffmanTree createHuffmanTree(const int *w, int n) {//n为叶子节点个数
    int m=2*n-1;
    //1.申请2n个空间,预留一个0号位置
    HuffmanTree tree=malloc(sizeof(HuffmanNode)*(m+1));//tree是结构体数组指针
    if(tree==NULL) {
        return NULL;
    }
    //2.1 初始化1--2n-1个节点(0号空着)
    for(int i=1;i<=m;i++) {
        tree[i].parent=tree[i].lChild=tree[i].rChild=0;//结构体数组里面存的是结构体所以用.tree[i]=*(tree+i)-->就是结构体
        tree[i].weight=0;//先给所有节点的权值赋值为0
    }
    //2.2初始化权值1--n(目标节点)
    for(int i=1;i<=n;i++) {
        tree[i].weight=w[i-1];//i从1开始,w[i]是另外的权值数据数组(从0开始存数据-->所以i-1)
    }
    //初始化结束,开始构建HuffmanTree
    //填充n+1下标到m下标的空间
    int s1,s2;//用于保存无parent约束的两个最小权值的编号
    for(int i=n+1;i<=m;i++) {//i++可以看作在创建父节点
        //在[1...i-1]范围内找父节点为0,权值最小的两个
        selectTwoMin(tree,i-1,&s1,&s2);//要找到是i上面的节点(i是提前下移了指向空的空间)-->所以i-1
        //将这2个权值最小的节点,组合到第i个位置
        tree[s1].parent=tree[s2].parent=i;//将此时s1和s2的父节点设为i
        tree[i].lChild=s1;                //父节点左边放最小
        tree[i].rChild=s2;                //父节点右边放次小
        tree[i].weight=tree[s1].weight+tree[s2].weight;//创建的父节点的权值为子左右节点权值相加
    }
    return tree;
}

void releaseHuffmanTree(HuffmanTree tree) {
    if(tree!=NULL) {
        free(tree);
    }
}

// 从n个叶子节点找到根节点，逆向求每个叶子的对应的编码
HuffmanCode* createHuffmanCodes(HuffmanTree tree, int n) {
    // 申请了一个数组空间，每个元素都保存一个地址，这个地址指向了对应元素的编码结果
    //HuffmanCode 是 char* 的别名，因此 HuffmanCode* 本质是 char**（二级指针）
    HuffmanCode* codes = malloc(sizeof(HuffmanCode) * n);// 存储n个符号的编码（数组元素为字符串指针）
    if (codes == NULL) {//分配失败
        return NULL;
    }
    memset(codes, 0, sizeof(HuffmanCode) * n);//将codes数组的所有元素n个（字符串指针）初始化为 NULL
    // 生成每个符号对应的编码结果
    // n个节点，树的高度最大为n，而HuffmanTree的高度要低于任意树的最大值,编码最长为n-1位,+1是防止溢出,第n位存\0(下标为n-1)
    char *temp = malloc(sizeof(char) * (n + 1));//申请临时缓冲区temp，用于存储编码的顺序是逆向遍历结果

    for (int i = 1; i <= n; ++i) {
        int start = n - 1;			// 标识temp空间的编码起始位置，从后往前编码,编码临时结果从后往前
        temp[start] = '\0';         // \0放在下标n-1（缓冲区倒数第二个位置），前面0~n-2共n-1个位置，刚好容纳最长n-1位编码
        int pos = i;				// 当前正在编码的节点-->叶节点（初始为叶子节点i）
        int p = tree[i].parent;		// 存放当前节点的父节点信息
        //逆向追溯生成编码
        while (p!=0) {//从叶节点向上找根(根节点的父节点为0,即p=0)
            --start;   // start往前移一位，为当前编码位预留存储位置（倒序存放)
            temp[start] = (tree[p].lChild == pos) ? '0' : '1';//如果当前p节点的左孩子是pos,在temp[start]此时位置存0,否则存1(哈夫曼树的所有非叶子节点度都为 2（必有左、右两个子节点），因此从任意叶子节点向上追溯时，该叶子节点必然是其父节点的左 / 右子节点之一，对应编码只能是 0 或 1，无其他可能)
            pos = p;                                          //将pos更新到p的位置(向上移动一层)
            p = tree[p].parent;                               //p更新到自己当前的父节点上(原先根节点,到根节点停下)
        }
        // 将第i个字符编码进行填充
        //上面申请的是指针数组的空间存指针,数量由叶节点决定;下面的申请是数组里元素指针指向的空间存的是字符,数量由树的高度决定(二级指针的应用)
        codes[i - 1] = malloc(sizeof(char) * (n - start));//每个节点的编码和长度并不相同,需要的空间也不相同,所需空间:n-start(n是总数,start是从后面开始插,有效长度是后面的,start此时的位置是前面无效的长度,所以n-start)
        strcpy(codes[i - 1], &temp[start]);// 将temp中从start开始的字符串（正向编码）复制到codes[i-1](temp是从后面开始插人的,插入是倒序,复制是从最后插入位置开始,最后就是正序了)
    }
    free(temp);//释放临时temp
    return codes;
}

void releaseHuffmanCode(HuffmanCode *codes,int n) {
    if(codes!=NULL) {
        for(int i=0;i<n;i++) {//编码的空间都释放掉
            if (codes[i]) {
                free(codes[i]);
            }
        }
        free(codes);
    }
}
/*strcpy的作用:char *strcpy(char *dest, const char *src);
*功能：把 src 指向的字符串（从 src 开始，直到 '\0' 结束）完整复制到 dest 指向的内存空间（包括 '\0'）；
要求：dest 必须有足够的内存容纳 src 的字符串（否则会内存越界）。
 *codes 是二级指针（char**），codes[i-1] 是第 i 个叶子节点的编码存储地址（char*）
 *&temp[start],&temp[start],本身只指向一个字符,函数会从这个字符开始，不断向后读取，直到找到\0才停止，从而获取完整字符串
 */