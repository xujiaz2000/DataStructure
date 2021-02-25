#include <stdio.h>
#include "Queue.h"

void Print(Queue ptrQ) {
    printf("(fornt)-> ");
    for (int i = ptrQ->front; i != ptrQ->rear; i = (i + 1) % ptrQ->maxSize)
        printf("%d ", ptrQ->data[i]);
    printf("(rear)\n");
    return ;
}

int main() 
{
    Queue ptrQ = CreateQueue(32);
    printf("Is Full: %d, Is Empty: %d\n", IsFull(ptrQ), IsEmpty(ptrQ));
    for (ElementType i = 0; i < 33; ++i)
        AddQ(i, ptrQ);  //因为实际容量为maxSize-1，所以会报两次“队列满”
    for (int i = 0; i < 10; ++i)
        DeleteQ(ptrQ);
    for (ElementType i = 0; i < 5; ++i)
        AddQ(i, ptrQ);
    Print(ptrQ);
    return 0;
}