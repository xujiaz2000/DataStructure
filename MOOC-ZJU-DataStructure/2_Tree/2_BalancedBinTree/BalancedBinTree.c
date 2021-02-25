#include <stdio.h>
#include <stdlib.h>
#include "BalancedBinTree.h"

int Max(int a, int b) {
    return (a > b? a: b);
}

/* 计算树高 */
int GetHeight(AVLTree a) {
    if (!a) return -1;  //定义只含根结点的树高度为0
    return a->height;
}

/* 左单旋 */
AVLTree SingleLeftRotation(AVLTree a) {
    // 注：a必须有一个左子结点b
    // 将a与b做左单旋，更新a和b的高度，返回新的根结点b
    AVLTree b = a->left;
    a->left = b->right;
    b->right = a;
    a->height = Max(GetHeight(a->left), GetHeight(a->right)) + 1;
    b->height = Max(GetHeight(b->left), a->height) + 1;
    return b;
}

/* 右单旋 */
AVLTree SingleRightRotation(AVLTree a) {
    AVLTree b = a->right;
    a->right = b->left;
    b->left = a;
    a->height = Max(GetHeight(a->left), GetHeight(a->right)) + 1;
    b->height = Max(a->height, GetHeight(b->right)) + 1;
    return b;
}

/* 左右双旋 */
AVLTree DoubleLeftRightRotation(AVLTree a) {
    // 注：a必须有一个左子结点b，且b必须有一个右子结点c
    // 将a、b与c做两次单旋，返回新的根结点c

    // 将b与c做右单旋，c被返回
    a->left = SingleRightRotation(a->left);
    // 将a与c做左单旋，c被返回
    return SingleLeftRotation(a);
}

/* 右左双旋 */
AVLTree DoubleRightLeftRotation(AVLTree a) {
    a->right = SingleLeftRotation(a->right);
    return SingleRightRotation(a);
}

/* AVL树的插入 */
AVLTree Insert(AVLTree a, ElementType x) {
    // 将x插入AVL树T中，并且返回调整后的AVL树
    if (!a) {
        a = (AVLTree)malloc(sizeof(struct AVLNode));
        a->data = x;
        a->left = a->right = NULL;
        a->height = 0;
    }
    else if (x > a->data) {
        a->right = Insert(a->right, x);  //插入到a的右子树
        // 如果需要右旋
        if (GetHeight(a->right) - GetHeight(a->left) == 2)
            if (x > a->right->data)
                a = SingleRightRotation(a);  //右单旋
            else
                a = DoubleRightLeftRotation(a);  //右左双旋
    }
    else if (x < a->data) {
        a->left = Insert(a->left, x);  //插入到a的左子树
        // 如果需要左旋
        if (GetHeight(a->left) - GetHeight(a->right) == 2)
            if (x < a->left->data)
                a = SingleLeftRotation(a);  //左单旋
            else
                a = DoubleLeftRightRotation(a);  //左右双旋
    }
    // else x == a->data， 无须插入

    //更新树高
    a->height = Max(GetHeight(a->left), GetHeight(a->right)) + 1;

    return a;
}

/* 层序遍历 */
void LevelOrderTraversal(AVLTree a) {
    AVLTree q[100] = {NULL};  //非循环队列，只能处理结点数小于数组容量的树
    int front = 0, rear = 0;
    if (!a) return ;
    q[rear++] = a;
    while (front != rear) {
        AVLTree t = q[front++];
        if (t == NULL) {
            printf("- ");  //空结点输出-
            continue;
        }
        else
            printf("%d ", t->data);
        if (t->left)
            q[rear++] = t->left;
        else 
            ++rear;
        if (t->right)
            q[rear++] = t->right;    
        else 
            ++rear; 
    }
    putchar(10);
    return ;
}

