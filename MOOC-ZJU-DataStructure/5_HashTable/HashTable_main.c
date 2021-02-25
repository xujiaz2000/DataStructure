#include <stdio.h>
#include "HashTable.h"

int main() 
{
    HashTable h = CreateHashTable(10);
    printf("HashTable size: %d\n", h->tableSize);
    ElementType a[] = {47, 7, 29, 11, 9, 84, 54, 20, 30};
    for (int i = 0; i < 9; ++i)
        Insert(h, a[i]);
    printf("pos of 29: %d\n", Find(h, 29));
    printf("can't find 21 (0/1): %d\n", h->cells[Find(h, 21)].info);
    return 0;
}
