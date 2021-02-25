#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayBinTree.h"

Position LeftChild(Position i) {
    return (2 * i + 1);
}

Position RightChild(Position i) {
    return (2 * i + 2);
}

/* 建树 */
BinTree CreateBinTree(int maxSize)  {
    BinTree bt = (BinTree)malloc(sizeof(struct BinTreeNode));
    bt->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    memset(bt->data, NIL, maxSize * sizeof(ElementType));
    bt->maxSize = maxSize;
    bt->nodeNum = 0;

    scanf("%d", &(bt->nodeNum));
    int i = 0;
    int j = 0;
    while (i < bt->nodeNum) {
        int val;
        scanf("%d", &val);
        if (val != NIL)
            ++i;
        bt->data[j++] = val;
    }
    return bt;
}

/* 判断树是否空 */
bool IsEmpty(BinTree bt) {
    return (bt->nodeNum == 0);
}

/* 前序遍历 */
void PreOrderTraversal(BinTree bt, Position i) {
    if (bt->data[i] != NIL) {
        printf("%d ", bt->data[i]);
        PreOrderTraversal(bt, LeftChild(i));
        PreOrderTraversal(bt, RightChild(i));
    }
    return ;
}

/* 中序遍历 */
void InOrderTraversal(BinTree bt, Position i) {
    if (bt->data[i] != NIL) {
        InOrderTraversal(bt, LeftChild(i));
        printf("%d ", bt->data[i]);
        InOrderTraversal(bt, RightChild(i));
    }
    return ;
}

/* 后序遍历 */
void PostOrderTraversal(BinTree bt, Position i) {
    if (bt->data[i] != NIL) {
        PostOrderTraversal(bt, LeftChild(i));
        PostOrderTraversal(bt, RightChild(i));
        printf("%d ", bt->data[i]);
    }
    return ;
}

/* 层次遍历 */
void LevelOrderTraversal(BinTree bt) {
    int i = 0;
    int j = 0;
    while (i < bt->nodeNum) {
        if (bt->data[j] != NIL) {
            ++i;
            printf("%d ", bt->data[j]);
        }
        ++j;
    }
    return ;
}