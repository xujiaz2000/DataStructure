#include <stdio.h>
#include "ArrayBinTree.h"

int main()
{
    BinTree bt = CreateBinTree(32);
    printf("IsEmpty: %d\n", IsEmpty(bt));
    PreOrderTraversal(bt, 0); putchar(10);
    InOrderTraversal(bt, 0); putchar(10);
    PostOrderTraversal(bt, 0); putchar(10);
    LevelOrderTraversal(bt); putchar(10);
    return 0;
}