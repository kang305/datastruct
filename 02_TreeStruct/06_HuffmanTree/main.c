#include"HuffmanTree.h"
#include<stdio.h>
#include<stdlib.h>
void testHuffmanTree() {

}
int main() {
    int w[]={5,29,7,8,14,23,3,11};
    char show[]={'A','B','C','D','E','F','G','H'};
    HuffmanTree tree=createHuffmanTree(w,sizeof(w)/sizeof(w[0]));
    int n=8;
    for (int i=1;i<2*n;i++) {
        printf("%d------%d,%d,lChild:%d,rChild:%d\n",i,tree[i].weight,tree[i].parent,tree[i].lChild,tree[i].rChild);
    }
printf("\n");
    HuffmanCode *codes=createHuffmanCodes(tree,n);
    for(int i=0;i<n;i++) {
        printf("%c : %s\n",show[i],codes[i]);
    }
    releaseHuffmanCode(codes,n);
    return 0;
}