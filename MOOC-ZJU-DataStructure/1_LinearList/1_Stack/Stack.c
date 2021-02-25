#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Stack CreateStack(int maxSize) {
    Stack s = (Stack)malloc(sizeof(struct SNode));
    s->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    s->top = 0;
    s->maxSize = maxSize;
    return s;
}

bool IsFull(Stack s) {
    return (s->maxSize == s->top);
}

bool IsEmpty(Stack s) {
    return (s->top == 0);
}

bool Push(Stack s, ElementType x) {
    if (s->top + 1 > s->maxSize) {
        printf("栈满");
        return false;
    }
    s->data[s->top++] = x;
    return true;
}

ElementType Pop(Stack s) {
    if (s->top == 0) {
        printf("栈空");
        exit(0);
    }
    ElementType x = s->data[--s->top];
    return x;
}

