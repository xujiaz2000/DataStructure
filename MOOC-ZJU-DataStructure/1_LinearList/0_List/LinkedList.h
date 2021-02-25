/******************************************************
 * 线性表的链式存储实现
 *  - ElementType可自定义
 * 
 * 注：
 * - 下标总是以0开始
 * - 首结点类型与普通结点无异。数据源存储链表有效长度，指针域存储第一个有效结点
 ******************************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdbool.h>

/* 数据对象集 */
typedef int ElementType;
typedef int Position;
#define MAXSIZE 1024
#define ERROR NULL

typedef struct LNode *PtrToLNode;
typedef PtrToLNode List;
struct LNode {
    ElementType data;
    PtrToLNode next;
};
// struct LNode l;
// List ptrL;

/* 操作集合 */
List MakeEmpty();
PtrToLNode FindKth(Position k, List ptrL);
PtrToLNode Find(ElementType x, List ptrL);
bool Insert(ElementType x, Position i, List ptrL);
bool Delete(Position i, List ptrL);
int Length(List ptrL);
bool PushBack(ElementType x, List ptrL);

#endif
