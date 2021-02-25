#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

List MakeEmpty() {
    List ptrL = (List)malloc(sizeof(struct LNode));
    ptrL->data = 0;
    ptrL->next = NULL;
    return ptrL;
}

PtrToLNode FindKth(Position k, List ptrL) {
    if (k < 0 || k >= ptrL->data)
        return NULL;
    Position i = 0;
    PtrToLNode p = ptrL->next;
    while (i < k) {
        p = p->next;
        ++i;
    }
    return p;
}

PtrToLNode Find(ElementType x, List ptrL) {
    PtrToLNode p = ptrL->next;
    while (p != NULL && p->data != x)
        p = p->next;
    return p;
}

bool Insert(ElementType x, Position i, List ptrL) {
    PtrToLNode p;
    if (i == 0)
        p = ptrL;
    else
        p = FindKth(i - 1, ptrL);
    if (p == NULL) {
        printf("插入位置非法");
        return false;
    }
    PtrToLNode tmp = (PtrToLNode)malloc(sizeof(struct LNode));
    tmp->data = x;
    tmp->next = p->next;
    p->next = tmp;
    ptrL->data += 1;
    return true;
}

bool Delete(Position i, List ptrL) {
    PtrToLNode p;
    if (i == 0)
        p = ptrL;
    else
        p = FindKth(i - 1, ptrL);
    if (p == NULL || p->next == NULL) {
        printf("删除位置非法");
        return false;
    }
    PtrToLNode tmp = p->next;
    p->next = tmp->next;
    free(tmp);
    ptrL->data -= 1;
    return true;
}

int Length(List ptrL) {
    return ptrL->data;
}

bool PushBack(ElementType x, List ptrL) {
    return Insert(x, ptrL->data, ptrL);    
}
