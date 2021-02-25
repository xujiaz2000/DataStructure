#include <stdio.h>
#include <stdlib.h>
#include "BinSearchTree.h"

int main()
{
    BinTree bst = CreateBinTree();
    printf("%c is found\n", Find(bst, 'a')->data);
    printf("%c is the min elem\n", FindMin(bst)->data);
    printf("%c is the max elem\n", FindMax(bst)->data);
    Insert(bst, 'i');
    Insert(bst, 'h');
    LevelOrderTraversal(bst); putchar(10);
    Delete(bst, 'e');
    LevelOrderTraversal(bst); putchar(10);
    Delete(bst, 'g');
    LevelOrderTraversal(bst); putchar(10);
    return 0;
}

//测试输入：gba##edc###f###
