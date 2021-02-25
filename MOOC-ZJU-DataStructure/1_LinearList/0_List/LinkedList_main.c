#include <stdio.h>
#include "LinkedList.h"

void Print(List ptrL) {
    PtrToLNode p = ptrL->next;
    for (int i = 0; i < ptrL->data; ++i) {
        printf("%d ", p->data);
        p = p->next;
    }
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
    PtrToLNode i = Find(1, l);
    printf("%d is found\n", i->data);
    PtrToLNode x = FindKth(1, l);
    printf("the %dth element is %d\n", 1, x->data);
    PushBack(2, l);
    PushBack(3, l);
    Print(l);
    return 0;
}