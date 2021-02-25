#include <stdio.h>
#include <stdlib.h>
#include "BinSearchTree.h"

Position Find_Recursion(BinTree bst, ElementType x) {
    if (!bst)
        return NULL;
    if (x > bst->data)
        return Find(bst->right, x);
    else if (x < bst->data)
        return Find(bst->left, x);
    else
        return bst;
}

Position Find(BinTree bst, ElementType x) {
    while (bst) {
        if (x > bst->data)
            bst = bst->right;
        else if (x < bst->data)
            bst = bst->left;
        else
            return bst;
    }
    return NULL;
}

Position FindMin_Recursion(BinTree bst) {
    if (!bst) return NULL;
    else if (!bst->left)
        return bst;
    else
        return FindMin_Recursion(bst->left);
}

Position FindMin(BinTree bst) {
    if (!bst) return NULL;
    while (bst->left)
        bst = bst->left;
    return bst;
}

Position FindMax(BinTree bst) {
    if (!bst) return NULL;
    while (bst->right)
        bst = bst->right;
    return bst;
}

BinTree Insert_Recursion(BinTree bst, ElementType x) {
    if (!bst) {
        bst = (BinTree)malloc(sizeof(struct TreeNode));
        bst->data = x;
        bst->left = bst->right = NULL;
    }
    else {
        if (x > bst->data)
            bst->right = Insert_Recursion(bst->right, x);
        else if(x < bst->data)
            bst->left = Insert_Recursion(bst->left, x);
        /* 若x已存在，什么也不做 */
    }
    return bst;
}

void Insert(BinTree bst, ElementType x) {
    if (!bst) {
        bst = (BinTree)malloc(sizeof(struct TreeNode));
        bst->data = x;
        bst->left = bst->right = NULL;
        return ;
    }
    BinTree t = bst;
    while (true) {
        if (x > t->data) {
            if (t->right) {
                t = t->right;
                continue;
            }
            else {
                BinTree tmp = (BinTree)malloc(sizeof(struct TreeNode));
                tmp->data = x;
                tmp->left = tmp->right = NULL;
                t->right = tmp;
                break;
            }
        }
        else if (x < t->data) {
            if (t->left) {
                t = t->left;
                continue;
            }
            else {
                BinTree tmp = (BinTree)malloc(sizeof(struct TreeNode));
                tmp->data = x;
                tmp->left = tmp->right = NULL;
                t->left = tmp;
                break;
            }
        }
        else  /* 若x已存在，什么也不做 */
            break;
    }
    return ;
}

BinTree Delete(BinTree bst, ElementType x) {
    Position tmp;
    if (!bst) {
        printf("未找到要删除的元素\n");
        return NULL;
    }
    if (x > bst->data)
        bst->right = Delete(bst->right, x);
    else if (x < bst->data)
        bst->left = Delete(bst->left, x);
    else {  //找到要删除结点
        if (bst->left && bst->right) {  //被删结点有左右两个子结点
            tmp = FindMin(bst->right);  //取右子树中的最小元素代替
            bst->data = tmp->data;
            bst->right = Delete(bst->right, tmp->data);  //任务变为，在删除结点的右子树中删除最小元素
        }
        else {  //被删结点只有一个子树
            tmp = bst;
            if (!bst->left)  //有右孩子或无子结点
                bst = bst->right;
            else if (!bst->right)
                bst = bst->left;
            free(tmp);
        }
    }
    return bst;
}