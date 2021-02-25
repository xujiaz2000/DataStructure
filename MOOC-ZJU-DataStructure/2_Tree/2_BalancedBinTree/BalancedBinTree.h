/******************************************************
 * 平衡二叉树（AVL树）：空树，或任意结点左、右子树高度差的绝对值不超过1
 ******************************************************/

#ifndef BALANCEDBINTREE_H
#define BALANCEDBINTREE_H

/* 数据对象集 */
typedef int ElementType;
typedef struct AVLNode *Position;

typedef struct AVLNode *AVLTree; 
struct AVLNode {
    ElementType data;
    AVLTree left;
    AVLTree right;
    int height;  //树高
};

/* 操作集 */
AVLTree SingleLeftRotation(AVLTree a);          //左单旋
AVLTree DoubleLeftRightRotation (AVLTree a);    //左右双旋
AVLTree SingleRightRotation(AVLTree a);         //右单旋
AVLTree DoubleRightLeftRotation(AVLTree a);     //右左双旋
AVLTree Insert(AVLTree a, ElementType x);
void LevelOrderTraversal(AVLTree bt);

#endif