#include <stdio.h>
#include "LinkedHashTable.h"

int main() 
{
    HashTable h = CreateHashTable(10);
    printf("HashTable size: %d\n", h->tableSize);
    ElementType a[] = {"acos", "atan", "char", "ceil", "define", "exp", "float", "floor"};
    for (int i = 0; i < 9; ++i)
        Insert(h, a[i]);
    printf("pos of \"char\": %s\n", Find(h, "char")->data);
    printf("pos of \"define\": %s\n", Find(h, "define")->data);
    printf("can't find \"hh\" (0/1): %d\n", Find(h, "hh") == NULL);
    return 0;
}
