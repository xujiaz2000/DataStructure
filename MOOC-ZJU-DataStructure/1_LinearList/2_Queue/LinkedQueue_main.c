#include <stdio.h>
#include "LinkedQueue.h"

void Print(Queue ptrQ) {
    printf("(fornt)->");
    PtrToNode p = ptrQ->front->next;  //p指向第一个有效结点
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("<-(rear)\n");
    return ;
}

int main() 
{
    Queue ptrQ = CreateQueue();
    printf("Is Empty: %d\n", IsEmpty(ptrQ));
    for (ElementType i = 0; i < 33; ++i) {
        AddQ(i, ptrQ);
        Print(ptrQ);
    }
    for (int i = 0; i < 10; ++i) {
        DeleteQ(ptrQ);
        Print(ptrQ);
    }
    for (ElementType i = 0; i < 5; ++i) {
        AddQ(i, ptrQ);
        Print(ptrQ);
    }
    return 0;
}