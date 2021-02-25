/******************************************************
 * 队列：具有一定操作约束的线性表
 *  - 只能在一端插入，在另一端删除
 * 
 * 队列的链式存储实现
 *  - 首结点同普通结点一样，其数据域存储队列长度
 *  - ElementType可自定义
 *  - 单链表：front->( )->( )->...->( )<-rear
 ******************************************************/

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
#include <stdbool.h>

/* 数据对象集 */
typedef int ElementType;

typedef struct Node *PtrToNode;
struct Node {
    ElementType data;
    PtrToNode next;
};

typedef struct QNode *Queue;
struct QNode {
    PtrToNode front;  //首指针
    PtrToNode rear;   //尾指针
};

/* 操作集 */
Queue CreateQueue();
bool IsEmpty(Queue ptrQ);
void AddQ(ElementType x, Queue ptrQ);  //入队
ElementType DeleteQ(Queue ptrQ);  //出队

#endif
