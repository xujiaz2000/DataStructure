#include <stdio.h>
#include "Stack.h"

void Print(Stack s) {
    for (int i = 0; i < s->top; ++i)
        printf("%d ", s->data[i]);
    printf("(top)\n");
    return ;
}

int main()
{
    Stack s = CreateStack(32);
    printf("is full: %d\nis empty: %d\n", IsFull(s), IsEmpty(s));
    Push(s, 0); Push(s, 1); Push(s, 2); Push(s, -1);
    Print(s);
    ElementType x = Pop(s);
    printf("pop: %d\n", x);
    Print(s);
    return 0;
}