#include <stdio.h>
#include <stdlib.h>
#include "LinkedQueue.h"

Queue CreateQueue() {
    PtrToNode ptrN = (PtrToNode)malloc(sizeof(struct Node));
    ptrN->data = 0; 
    ptrN->next = NULL;
    Queue ptrQ = (Queue)malloc(sizeof(struct QNode));
    ptrQ->front = ptrN;
    ptrQ->rear = ptrN;
    return ptrQ;
}

bool IsEmpty(Queue ptrQ) {
    return (ptrQ->front->data == 0);
}

void AddQ(ElementType x, Queue ptrQ) {
    PtrToNode ptrN = (PtrToNode)malloc(sizeof(struct Node));
    ptrN->data = x;
    ptrN->next = NULL;
    ptrQ->rear->next = ptrN;
    ptrQ->rear = ptrN;
    ptrQ->front->data += 1;
    return ;
}

ElementType DeleteQ(Queue ptrQ) {
    if (IsEmpty(ptrQ)) {
        printf("队列空\n");
        exit(0);
    }
    PtrToNode firstNode = ptrQ->front->next;
    ElementType x = firstNode->data;
    ptrQ->front->next = firstNode->next;
    free(firstNode);
    ptrQ->front->data -= 1;
    return x;
}