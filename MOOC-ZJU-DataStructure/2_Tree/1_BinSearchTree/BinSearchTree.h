/******************************************************
 * 二叉搜索树：左子树所有结点小于根结点，右子树所有结点大于根结点
 * 
 * - 这里不允许存相同元素
 ******************************************************/

#ifndef BINSEARCHTREE_H
#define BINSEARCHTREE_H
#include "../0_BinTree/BinTree.h"

typedef struct TreeNode *Position;

/* 操作集 */
Position Find(BinTree bst, ElementType x);
Position FindMin(BinTree bst);
Position FindMax(BinTree bst);
void Insert(BinTree bst, ElementType x);
BinTree Insert_Recursion(BinTree bst, ElementType x);
BinTree Delete(BinTree bst, ElementType x);

#endif