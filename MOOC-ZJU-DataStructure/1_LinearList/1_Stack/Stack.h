/******************************************************
 * 栈：具有一定操作约束的线性表
 *  - 只能在一端（栈顶，Top）做插入、删除
 * 
 * 栈的顺序存储实现
 *  - ElementType可自定义
 *  - 注：下标总是以0开始
 ******************************************************/

#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

/* 数据对象集 */
typedef int ElementType;
typedef int Position;

typedef struct SNode *Stack;
struct SNode {
    ElementType *data;
    Position top;  // 尾后指针，亦可表示栈内元素数
    int maxSize;
};

/* 操作集 */
Stack CreateStack(int maxSize);
bool IsFull(Stack s);
bool IsEmpty(Stack s);
bool Push(Stack s, ElementType x);
ElementType Pop(Stack s);

#endif
