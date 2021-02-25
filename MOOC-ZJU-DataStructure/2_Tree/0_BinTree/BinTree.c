#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

BinTree CreateBinTree() {    
    //先序遍历方式建树
    ElementType t;
    scanf("%c", &t);
    if (t == '#') 
        return NULL;
    BinTree root = (BinTree)malloc(sizeof(struct TreeNode));
    root->data = t;
    root->left = CreateBinTree();
    root->right = CreateBinTree();
    return root;
}

bool IsEmpty(BinTree bt) {
    return (bt == NULL);
}

/* 先序遍历的递归实现 */
void PreOrderTraversal_Recursion(BinTree bt) {
    if (bt) {
        printf("%c ", bt->data);
        PreOrderTraversal_Recursion(bt->left);
        PreOrderTraversal_Recursion(bt->right);
    }
    return ;
}

/* 先序遍历的非递归实现 */
void PreOrderTraversal(BinTree bt) {
    //左侧链 + 右子树
    BinTree s[100];  //栈，数组容量限制了可处理树的大小
    int top = 0;
    BinTree t = bt;
    while (t || top != 0) {
        while (t) {  //将当前结点所在的左侧链压入栈
            s[top++] = t;
            printf("%c ", t->data);
            t = t->left;
        }
        if (top != 0) {
            t = s[--top];
            t = t->right;  //当前结点转向右子树
        }
    }
    return ;
}

/* 先序遍历的非递归实现：方法二 */
void PreOrderTraversal_2(BinTree bt) {
    //相当于将层序遍历中的队列改为栈
    //根 - 左 - 右
    //口诀：单条件while循环，无脑出栈入栈
    if (!bt) return ;
    char res[100];  //保存后序遍历序列
    int p = 0;  //指向res数组
    BinTree s[100];  //栈
    int top = 0;
    s[top++] = bt;
    while (top != 0) {
        BinTree tmp = s[--top];
        res[p++] = tmp->data;
        if (tmp->right)
            s[top++] = tmp->right;
        if (tmp->left)
            s[top++] = tmp->left;
    }
    //输出
    for (int i = 0; i < p; ++i)
        printf("%c ", res[i]);
    return ;
}

/* 中序遍历的递归实现 */
void InOrderTraversal_Recursion(BinTree bt) {
    if (bt) {
        InOrderTraversal_Recursion(bt->left);
        printf("%c ", bt->data);
        InOrderTraversal_Recursion(bt->right);
    }
    return ;
}

/* 中序遍历的非递归实现 */
void InOrderTraversal(BinTree bt) {
    //左侧链 + 右子树
    BinTree s[100]; //栈
    int top = 0;
    BinTree t = bt;
    while (t || top != 0) {
        while (t) {  //将当前结点所在的左侧链压入栈
            s[top++] = t;
            t = t->left;
        }
        if (top != 0) {
            t = s[--top];
            printf("%c ", t->data);
            t = t->right;  //当前结点转向右子树
        }
    }
    return ;
}

/* 后序遍历的递归实现 */
void PostOrderTraversal_Recursion(BinTree bt) {
    if (bt) {
        PostOrderTraversal_Recursion(bt->left);
        PostOrderTraversal_Recursion(bt->right);
        printf("%c ", bt->data);
    }
    return ;
}

/* 后序遍历的非递归实现 */
void PostOrderTraversal(BinTree bt) {
    //左侧链 + 右子树
    //左 右 根
    BinTree s[100];  //栈
    int top = 0;
    BinTree flag = NULL;  //记录上一次访问完的子树的根结点
    BinTree t = bt;
    while (t || top != 0) {
        while (t) {  //将当前结点所在的左侧链压入栈
            s[top++] = t;
            t = t->left;
        }
        BinTree p = s[top - 1];
        if (p->right == NULL || p->right == flag) {  //栈顶元素的左子树在上一个while中已被访问；若栈顶结点的右子树为空或已被访问，打印该结点的值
            printf("%c ", p->data);
            flag = s[--top];
        }
        else
            t = p->right;  //当前结点转向右子树
    }
}

/* 后序遍历的非递归实现：方法二 */
void PostOrderTraversal_2(BinTree bt) {
    //相当于将层序遍历中的队列改为栈
    //类似于前序遍历的方法二，得到：根 - 右 - 左，然后翻转
    //口诀：单条件while循环，无脑出栈入栈
    if (!bt) return ;
    char res[100];  //保存后序遍历序列
    int p = 0;  //指向res数组
    BinTree s[100];  //栈
    int top = 0;
    s[top++] = bt;
    while (top != 0) {
        BinTree tmp = s[--top];
        res[p++] = tmp->data;
        if (tmp->left)
            s[top++] = tmp->left;
        if (tmp->right)
            s[top++] = tmp->right;
    }
    //翻转res数组
    int front = 0, rear = p - 1;
    while (front < rear) {
        char tmp = res[front];
        res[front] = res[rear];
        res[rear] = tmp;
        ++front;
        --rear;
    }
    //输出
    for (int i = 0; i < p; ++i)
        printf("%c ", res[i]);
    return ;
}

/* 层序遍历 */
void LevelOrderTraversal(BinTree bt) {
    BinTree q[100];  //非循环队列，只能处理结点数小于数组容量的树
    int front = 0, rear = 0;
    if (!bt) return ;
    q[rear++] = bt;
    while (front != rear) {
        BinTreeNode t = q[front++];
        printf("%c ", t->data);
        if (t->left)
            q[rear++] = t->left;
        if (t->right)
            q[rear++] = t->right;            
    }
    return ;
}

/* 输出二叉树中的叶子结点 */
void PreOrderPrintLeaves(BinTree bt) {
    if (bt) {
        if (!bt->left && !bt->right)
            printf("%c", bt->data);
        PreOrderPrintLeaves(bt->left);
        PreOrderPrintLeaves(bt->right);
    }
}

/* 求二叉树高度 */
int PostOrderGetHeight(BinTree bt) {
    if (!bt)
        return 0;
    int hl = PostOrderGetHeight(bt->left);
    int hr = PostOrderGetHeight(bt->right);
    return ((hl > hr)? hl: hr) + 1;
}
