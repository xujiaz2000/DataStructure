/******************************************************
 * 二叉树：若不为空，由根结点和左右二叉子树组成
 * 
 * 二叉树的顺序存储实现
 *  - 很适合存完全二叉树
 *  - 无论是否是，一律按完全二叉树存
 *  - 若不是完全二叉树，不存在结点位置存为空
 ******************************************************/

#ifndef ARRAYBINTREE_H
#define ARRAYBINTREE_H
#include <stdbool.h>

/* 数据对象集 */
typedef int ElementType;
typedef int Position;
#define NIL -1

typedef struct BinTreeNode *BinTree;
struct BinTreeNode {
    ElementType *data;
    int maxSize;
    int nodeNum;  //记录树所包含的节点数
};

/* 操作集 */
BinTree CreateBinTree(int maxSize);
bool IsEmpty(BinTree bt);
void PreOrderTraversal(BinTree bt, Position i);
void InOrderTraversal(BinTree b, Position it);
void PostOrderTraversal(BinTree bt, Position i);
void LevelOrderTraversal(BinTree bt);

#endif