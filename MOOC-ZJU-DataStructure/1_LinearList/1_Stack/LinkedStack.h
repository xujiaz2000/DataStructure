/******************************************************
 * 栈：具有一定操作约束的线性表
 *  - 只能在一端（栈顶，Top）做插入、删除
 * 
 * 栈的顺序存储实现
 *  - top指针指向首结点，即首结点时栈顶：top->( )->( )->...->( )
 *  - ElementType可自定义
 * 
 *  注：
 *  - 下标总是以0开始
 *  - 首结点类型与普通结点无异。数据源存储链表有效长度，指针域存储第一个有效结点
 ******************************************************/

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include <stdbool.h>

/* 数据对象集 */
typedef int ElementType;

typedef struct SNode *PtrToSNode;
struct SNode {
    ElementType data;
    PtrToSNode next;
};
typedef PtrToSNode Stack;

/* 操作集 */
Stack CreateStack();
bool IsEmpty(Stack s);
bool Push(Stack s, ElementType x);
ElementType Pop(Stack s);

#endif
