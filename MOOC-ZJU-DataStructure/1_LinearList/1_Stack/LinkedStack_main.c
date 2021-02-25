#include <stdio.h>
#include "LinkedStack.h"

void Print(Stack s) {
    printf("(top) ");
    for (PtrToSNode p = s->next; p != NULL; p = p->next)
        printf("%d ", p->data);
    printf("\n");
    return ;
}

int main()
{
    Stack s = CreateStack();
    printf("is empty: %d\n", IsEmpty(s));
    Push(s, 0); Push(s, 1); Push(s, 2); Push(s, -1);
    Print(s);
    ElementType x = Pop(s);
    printf("pop: %d\n", x);
    Print(s);
    return 0;
}