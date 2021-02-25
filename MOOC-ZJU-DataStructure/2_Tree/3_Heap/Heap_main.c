#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Heap.h"

void OrderlyPrintAndDeleteMax(MaxHeap h) {
    while (h->size != 0)
        printf("%d ", DeleteMax(h));
    putchar(10);
    return ;
}

void OrderlyPrintAndDeleteMin(MinHeap h) {
    while (h->size != 0)
        printf("%d ", DeleteMin(h));
    putchar(10);
    return ;
}

int main()
{
    MaxHeap h = CreateMaxHeap(32);
    printf("IsFull: %d\nIsEmpty: %d\n", IsFull(h), IsEmpty(h));
    ElementType elems[10] = {1, 4, 6, 5, 3, 2, 9, 7, 8, 0};
    memcpy(h->data + 1, elems, 10 * sizeof(ElementType));
    h->size = 10;
    BuildMaxHeap(h);
    OrderlyPrintAndDeleteMax(h);
    InsertForMaxHeap(h, 11); InsertForMaxHeap(h, 2); InsertForMaxHeap(h, 3); InsertForMaxHeap(h, 10); InsertForMaxHeap(h, 10); InsertForMaxHeap(h, 0);
    OrderlyPrintAndDeleteMax(h);
    printf("IsFull: %d\nIsEmpty: %d\n", IsFull(h), IsEmpty(h));

    MinHeap h2 = CreateMinHeap(32);
    printf("IsFull: %d\nIsEmpty: %d\n", IsFull(h2), IsEmpty(h2));
    memcpy(h2->data + 1, elems, 10 * sizeof(ElementType));
    h2->size = 10;
    BuildMinHeap(h2);
    OrderlyPrintAndDeleteMin(h2);
    InsertForMinHeap(h2, 11); InsertForMinHeap(h2, 2); InsertForMinHeap(h2, 3); InsertForMinHeap(h2, 10); InsertForMinHeap(h2, 10); InsertForMinHeap(h2, 0);
    OrderlyPrintAndDeleteMin(h2);
    printf("IsFull: %d\nIsEmpty: %d\n", IsFull(h2), IsEmpty(h2));

    return 0;
}