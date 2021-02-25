#include <stdio.h>
#include <stdlib.h>
#include "LinkedStack.h"

Stack CreateStack() {
    Stack s = (Stack)malloc(sizeof(struct SNode));
    s->data = 0;
    s->next = NULL;
    return s;
}

bool IsEmpty(Stack s) {
    return (s->data == 0);
}

bool Push(Stack s, ElementType x) {
    PtrToSNode tmp = (PtrToSNode)malloc(sizeof(struct SNode));
    if (!tmp) {
        printf("分配空间失败");
        return false;
    }
    tmp->data = x;
    tmp->next = s->next;
    s->next = tmp;
    s->data += 1;
    return true;
}

ElementType Pop(Stack s) {
    if (s->data == 0) {
        printf("栈空\n");
        exit(0);
    }
    PtrToSNode tmp = s->next;
    ElementType x = tmp->data;
    s->next = tmp->next;
    free(tmp);
    s->data -= 1;
    return x;
}
