#include <stdio.h>
#include "List.h"

void Print(List ptrL) {
    for (int i = 0; i < ptrL->last; ++i)
        printf("%d ", ptrL->data[i]);
    printf("(length: %d)", Length(ptrL));
    printf("\n");
    return ;
}

int main()
{
    List l = MakeEmpty();
    Insert(0, 0, l);
    Insert(1, 1, l);
    Insert(-1, 0, l);
    Insert(2, 1, l);
    Print(l);
    Delete(0, l);
    Delete(0, l);
    Print(l);
    Position i = Find(1, l);
    printf("1 is located at %dth\n", i);
    ElementType x = FindKth(1, l);
    printf("the %dth element is %d\n", 1, x);
    PushBack(2, l);
    PushBack(3, l);
    Print(l);
    return 0;
}