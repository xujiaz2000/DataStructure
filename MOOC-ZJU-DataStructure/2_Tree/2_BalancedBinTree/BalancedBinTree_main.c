#include <stdio.h>
#include <stdlib.h>
#include "BalancedBinTree.h"

int main()
{
    AVLTree a;
    a = Insert(a, 4); a = Insert(a, 3); a = Insert(a, 1); 
    a = Insert(a, 2); a = Insert(a, 5); a = Insert(a, 0);
    LevelOrderTraversal(a);
    return 0;
}