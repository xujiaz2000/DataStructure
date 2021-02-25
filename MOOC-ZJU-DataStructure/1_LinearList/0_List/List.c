#include <stdlib.h>
#include <stdio.h>
#include "List.h"

List MakeEmpty() {
    List ptrL;
    ptrL = (List)malloc(sizeof(struct LNode));
    ptrL->last = 0;
    return ptrL;
}

ElementType FindKth(Position k, List ptrL) {
    if (k >= ptrL->last) {
        printf("访问位置非法");
        exit(0);
    }
    return ptrL->data[k];
}

Position Find(ElementType x, List ptrL) {
    Position i = 0;
    while (i < ptrL->last && ptrL->data[i] != x)
        ++i;
    if (i == ptrL->last)  //没找到
        return ERROR;
    else 
        return i;
}

bool Insert(ElementType x, Position i, List ptrL){
    if (ptrL->last + 1 > MAXSIZE) {
        printf("线性表已满");
        return false;
    }
    if (i < 0 || i > ptrL->last) {
        printf("插入位置非法");
        return false;
    }
    for (Position j = ptrL->last; j > i; --j)
        ptrL->data[j] = ptrL->data[j - 1];
    ptrL->data[i] = x;
    ptrL->last += 1;
    return true;
}

bool Delete(Position i, List ptrL) {
    if (i < 0 || i >= ptrL->last) {
        printf("删除位置非法");
        return false;
    }
    for (Position j = i; j < ptrL->last - 1; ++j)
        ptrL->data[j] = ptrL->data[j + 1]; 
    ptrL->last -= 1;
    return true;
}

int Length(List PtrL) {
    return PtrL->last;
}

bool PushBack(ElementType x,List ptrL) {
    if (ptrL->last + 1 > MAXSIZE) {
        printf("线性表已满");
        return false;
    }
    ptrL->data[ptrL->last] = x;
    ptrL->last += 1;
    return true;
}
