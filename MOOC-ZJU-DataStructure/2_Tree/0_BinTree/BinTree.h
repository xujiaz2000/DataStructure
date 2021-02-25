/******************************************************
 * 二叉树：若不为空，由根结点和左右二叉子树组成
 * 
 * 二叉树的链式存储实现
 ******************************************************/

#ifndef BINTREE_H
#define BINTREE_H
#include <stdbool.h>

/* 数据对象集 */
typedef char ElementType;

typedef struct TreeNode *BinTree;
typedef struct TreeNode *BinTreeNode;
struct TreeNode {
    ElementType data; //结点数据
    BinTree left;     //指向左子树
    BinTree right;    //指向右子树
};

/* 操作集 */
BinTree CreateBinTree();
bool IsEmpty(BinTree bt);
void PreOrderTraversal_Recursion(BinTree bt);
void InOrderTraversal_Recursion(BinTree b);
void PostOrderTraversal_Recursion(BinTree bt);
void PreOrderTraversal(BinTree bt);
void InOrderTraversal(BinTree b);
void PostOrderTraversal(BinTree bt);
void PostOrderTraversal_2(BinTree bt);
void PreOrderTraversal_2(BinTree bt);
void LevelOrderTraversal(BinTree bt);

#endif