/******************************************************
 * 队列：具有一定操作约束的线性表
 *  - 只能在一端插入，在另一端删除
 * 
 * 队列的顺序存储实现
 *  - ElementType可自定义
 *  - 下标总是以0开始
 *  - ”循环使用“线性存储空间，采用“加1取余法”
 *      - 为防止在front==rear时有队列空还是队列满的歧义，限定实际队列容量为maxSize-1
 ******************************************************/


#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

/* 数据对象集 */
typedef int ElementType;
typedef int Position;

typedef struct QNode *Queue;
struct QNode {
    ElementType *data;
    Position front, rear;  //头指针，尾后指针
    int maxSize;
};

/* 操作集 */
Queue CreateQueue(int maxSize);
bool IsFull(Queue ptrQ);
bool IsEmpty(Queue ptrQ);
bool AddQ(ElementType x, Queue ptrQ);  //入队
ElementType DeleteQ(Queue ptrQ);  //出队

#endif