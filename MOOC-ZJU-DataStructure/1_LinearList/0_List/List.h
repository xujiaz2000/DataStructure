/******************************************************
 * 线性表的顺序存储实现
 *  - ElementType可自定义
 *  - 注：下标总是以0开始
 ******************************************************/

#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

/* 数据对象集 */
#define MAXSIZE 1024
#define ERROR -1
typedef int ElementType;
typedef int Position;

typedef struct LNode *List;
struct LNode {
    ElementType data[MAXSIZE];
    Position last;  //尾后指针，亦可表示线性表长度
};
// struct LNode l;
// List ptrL;

/* 操作集合 */
List MakeEmpty();
ElementType FindKth(Position k, List ptrL);
Position Find(ElementType x, List ptrL);
bool Insert(ElementType x, Position i, List ptrL);
bool Delete(Position i, List ptrL);
Position Length(List ptrL);
bool PushBack(ElementType x,List ptrL);

#endif
