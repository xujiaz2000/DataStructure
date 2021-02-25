#include <stdio.h>
#include <stdlib.h>
#include "../3_Heap/Heap.h"
#include "HuffmanTree.h"

HuffmanTree BuildHuffmanTree(MinHeap h) {  //MinHeap中的ElementType为HuffmanTree（改写较麻烦，下面的代码没有验证）
    //做法：利用最小堆选两个最小的结点，合并后插入最小堆，循环至最小堆中只有一个结点
    //T(N) = O(NlogN)
    HuffmanTree t;
    BuildMinHeap(h);
    for (int i = 0; i < h->size; ++i) {  //做h->size-1次合并
        t = (HuffmanTree)malloc(sizeof(struct TreeNode));
        t->left = DeleteMin(h);
        t->right = DeleteMin(h);
        t->weight = t->left->weight + t->right->weight;  //计算合并后结点的权值
        InsertForMinHeap(h, t);
    }
    t = DeleteMin(h);
    return t;
}

