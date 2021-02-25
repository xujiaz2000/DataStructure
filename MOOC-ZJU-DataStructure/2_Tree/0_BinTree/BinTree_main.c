#include <stdio.h>
#include "BinTree.h"

int main()
{
    BinTree bt = CreateBinTree();
    printf("递归实现的先中后序遍历：\n");
    PreOrderTraversal_Recursion(bt); putchar(10);
    InOrderTraversal_Recursion(bt); putchar(10);
    PostOrderTraversal_Recursion(bt); putchar(10);
    printf("非递归实现的先中后序遍历：\n");
    PreOrderTraversal(bt); putchar(10);
    InOrderTraversal(bt); putchar(10);
    PostOrderTraversal(bt); putchar(10);
    printf("层序遍历：\n");
    LevelOrderTraversal(bt); putchar(10);
    printf("非递归实现的先序遍历-方法二：\n");
    PreOrderTraversal_2(bt); putchar(10);
    printf("非递归实现的后序遍历-方法二：\n");
    PostOrderTraversal_2(bt); putchar(10);

    return 0;
}