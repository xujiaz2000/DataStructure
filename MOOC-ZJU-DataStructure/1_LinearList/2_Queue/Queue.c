#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

Queue CreateQueue(int maxSize) {
    Queue ptrQ = (Queue)malloc(sizeof(struct QNode));
    ptrQ->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    ptrQ->front = ptrQ->rear = 0;
    ptrQ->maxSize = maxSize;
    return ptrQ;
}

bool IsFull(Queue ptrQ) {
    return ((ptrQ->rear + 1) % ptrQ->maxSize == ptrQ->front);
}

bool IsEmpty(Queue ptrQ) {
    return (ptrQ->rear == ptrQ->front);
}

bool AddQ(ElementType x, Queue ptrQ) {
    if (IsFull(ptrQ)) {
        printf("队列满\n");
        return false;
    }
    ptrQ->data[ptrQ->rear] = x;
    ptrQ->rear = (ptrQ->rear + 1) % ptrQ->maxSize;
    return true;
}

ElementType DeleteQ(Queue ptrQ) {
    if (IsEmpty(ptrQ)) {
        printf("队列空\n");
        return false;
    }
    ElementType x = ptrQ->front;
    ptrQ->front = (ptrQ->front + 1) % ptrQ->maxSize;
    return x;
}