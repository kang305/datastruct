#ifndef DATASTRUCT2_HUFFMANTREE_H
#define DATASTRUCT2_HUFFMANTREE_H
/*Huffman树通过代编码的节点数量,计算出总共的节点个数m=2*n-1
 * 要牺牲用数组0的单元表示无效节点,从1号单元开始进行填充,那么申请2*n=m+1个空间
 */
typedef struct {
    int weight;//节点权值
    int parent;//父节点编号,0值表示该节点就是根(利用下标)
    int lChild, rChild;//指向该节点的左,右孩子节点的编号（0表示无对应孩子）
}HuffmanNode,*HuffmanTree;//HuffmanTree=HuffmanNode*

HuffmanTree createHuffmanTree(const int *w,int n);//传权值和叶子节点个数
void releaseHuffmanTree(HuffmanTree tree);//释放

/*Huffman编码,用一个字符数组空间来保存每个符号的编码字符串
 * char *codes[n]
 */
typedef char *HuffmanCode;//HuffmanCode=char * ,单个符号的编码（字符串形式，如"010"）
HuffmanCode* createHuffmanCodes(HuffmanTree tree, int n);
void releaseHuffmanCode(HuffmanCode *codes,int n);
#endif //DATASTRUCT2_HUFFMANTREE_H