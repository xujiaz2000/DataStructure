/******************************************************
 * 最大堆（MaxHeap）：完全二叉树，每个结点的元素值不小于子结点的元素值
 * 
 * 堆是优先队列的一种较好的实现方式，这里堆的实现采用数组表示的完全二叉树
 * 堆的两个特性（插入和删除操作都不应该破坏堆的结构性）
 *  - 结构性：（数组实现的）完全二叉树
 *  - 有序性：任一结点的关键字是其子树所有结点的最大值
 ******************************************************/

#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>

/* 数据对象集 */
typedef int ElementType;

typedef struct HeapNode *Heap; 
struct HeapNode {
    ElementType *data;  //存储堆元素的数组
    int size;           //堆的当前元素个数
    int capacity;       //堆的最大容量
};
typedef Heap MaxHeap;
typedef Heap MinHeap;

#define MAXDATA 1000   //哨兵，定义为大于堆中所有可能元素的值，作为堆数组的首元素
#define MINDATA -1000  //哨兵，被用于最小堆
#define ERROR -1  //删除失败返回的错误标识，应为堆中不可能出现的元素值

/* 操作集 */
MaxHeap CreateMaxHeap(int maxSize);
MinHeap CreateMinHeap(int maxSize);
bool IsFull(Heap h);
bool IsEmpty(Heap h);
bool InsertForMaxHeap(MaxHeap h, ElementType x);
bool InsertForMinHeap(MinHeap h, ElementType x);
ElementType DeleteMax(MaxHeap h);
ElementType DeleteMin(MinHeap h);
void BuildMaxHeap(MaxHeap h);
void BuildMinHeap(MinHeap h);

#endif
