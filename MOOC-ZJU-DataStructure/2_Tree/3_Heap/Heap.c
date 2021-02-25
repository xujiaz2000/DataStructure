#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

/* 创建容量为MaxSize的空的最大堆 */
MaxHeap CreateMaxHeap(int maxSize) {
    MaxHeap h = (MaxHeap)malloc(sizeof(struct HeapNode));
    h->data = (ElementType *)malloc((maxSize + 1) * sizeof(ElementType));
    h->data[0] = MAXDATA;  //定义"哨兵"为大于堆中所有可能元素的值
    h->size = 0;  //若堆非空，指向堆尾
    h->capacity = maxSize;
    return h;
}

/* 创建容量为MaxSize的空的最小堆 */
MinHeap CreateMinHeap(int maxSize) {
    MinHeap h = (MinHeap)malloc(sizeof(struct HeapNode));
    h->data = (ElementType *)malloc((maxSize + 1) * sizeof(ElementType));
    h->data[0] = MINDATA;  //定义"哨兵"为大于堆中所有可能元素的值
    h->size = 0;  //若堆非空，指向堆尾
    h->capacity = maxSize;
    return h;
}

bool IsFull(Heap h) {
    return (h->size == h->capacity);
}

bool IsEmpty(Heap h) {
    return (h->size == 0);
}

bool InsertForMaxHeap(MaxHeap h, ElementType x) {
    //将新增结点插入到尾后位置到根的有序序列中
    //h->data[0]已被定义为哨兵，所有x的上滤至多会在根结点结束
    if (IsFull(h)) {
        printf("插入失败，最大堆已满");
        return false;
    } 
    int i = ++h->size;  //i用来存储插入的位置
    while (h->data[i / 2] < x) {
        h->data[i] = h->data[i / 2];  //上滤x
        i /= 2;
    }
    h->data[i] = x;  //插入
    return true;
}

bool InsertForMinHeap(MinHeap h, ElementType x) {
    //将新增结点插入到尾后位置到根的有序序列中
    //h->data[0]已被定义为哨兵，所有x的上滤至多会在根结点结束
    if (IsFull(h)) {
        printf("插入失败，最小堆已满");
        return false;
    } 
    int i = ++h->size;  //i用来存储插入的位置
    while (h->data[i / 2] > x) {
        h->data[i] = h->data[i / 2];  //上滤x
        i /= 2;
    }
    h->data[i] = x;  //插入
    return true;
}

ElementType DeleteMax(MaxHeap h) {
    //从最大堆中取出最大的元素（根结点所有），并删除根结点，期间保证堆的有序性
    //做法：取出根结点的元素，将堆尾元素赋值给根，下滤根元素
    if (IsEmpty(h)) {
        printf("删除失败，最大堆为空");
        return ERROR;
    }
    ElementType maxData = h->data[1];
    int tmp = h->data[h->size--];
    int i = 1;  //i用来存储tmp应该在的位置
    while (2 * i <= h->size) {  //当tmp有左孩子
        i = 2 * i;
        if (i + 1 <= h->size && h->data[i + 1] > h->data[i])  //若tmp有右孩子，先找到左右孩子中较大者
            i += 1;
        if (tmp >= h->data[i]) {  //若tmp不小于左右孩子，下滤终止
            i /= 2;
            break;
        }
        h->data[i / 2] = h->data[i];  //成功下滤
    }
    h->data[i] = tmp;
    return maxData;
}

ElementType DeleteMin(MinHeap h) {
    //从最小堆中取出最小的元素（根结点所有），并删除根结点，期间保证堆的有序性
    //做法：取出根结点的元素，将堆尾元素赋值给根，下滤根元素
    if (IsEmpty(h)) {
        printf("删除失败，最大堆为空");
        return ERROR;
    }
    ElementType minData = h->data[1];
    int tmp = h->data[h->size--];
    int i = 1;  //i用来存储tmp应该在的位置
    while (2 * i <= h->size) {  //当tmp有左孩子
        i = 2 * i;
        if (i + 1 <= h->size && h->data[i + 1] < h->data[i])  //若tmp有右孩子，先找到左右孩子中较小者
            i += 1;
        if (tmp <= h->data[i]) {  //若tmp不大于左右孩子，下滤终止
            i /= 2;
            break;
        }
        h->data[i / 2] = h->data[i];  //成功下滤
    }
    h->data[i] = tmp;
    return minData;
}

/* 下滤：将H中以h->data[p]为根的子堆调整为最大堆（假设其左右子树已是最大堆） */
void PercDownForMaxHeap(MaxHeap h, int p) {
    ElementType x = h->data[p];  //x用来存储根结点存放的值，p用来存储x应该在的位置
    while (2 * p <= h->size) {  //当p有左孩子时
        p = 2 * p;
        if (p + 1 <= h->size && h->data[p + 1] > h->data[p])  //若p有右孩子，先找到左右孩子中较大者
            p += 1;
        if (x >= h->data[p]) {  //若p不小于左右孩子，下滤终止
            p /= 2;
            break;
        }
        h->data[p / 2] = h->data[p];  //下滤
    }
    h->data[p] = x;
    return ;
}

/* 下滤：将H中以h->data[p]为根的子堆调整为最大堆（假设其左右子树已是最大堆） */
void PercDownForMinHeap(MinHeap h, int p) {
    ElementType x = h->data[p];  //x用来存储根结点存放的值，p用来存储x应该在的位置
    while (2 * p <= h->size) {  //当p有左孩子时
        p = 2 * p;
        if (p + 1 <= h->size && h->data[p + 1] < h->data[p])  //若p有右孩子，先找到左右孩子中较小者
            p += 1;
        if (x <= h->data[p]) {  //若p不大于左右孩子，下滤终止
            p /= 2;
            break;
        }
        h->data[p / 2] = h->data[p];  //下滤
    }
    h->data[p] = x;
    return ;
}

/* 建（最大）堆：将已存在的N个元素按最大堆的要求存放到一个一维数组中
 *      方法一：一个一个插入到一个初始为空的堆中，T(N)=O(NlogN)
 *     *方法二：先将N个元素顺序存入（以满足堆的结构性），再调整各个结点的位置（以满足堆的有序性），T(N)=O(N)
 *      - 方法二的原理：若左右子树都是堆，只需将根结点下滤
 *      - 方法二的做法：从倒数第二层的最后向前遍历，下滤遍历到的每一个点
 */
void BuildMaxHeap(MaxHeap h) {
    //调整h->data[]中的元素，使满足最大堆的有序性
    //这里假设所有h->size个元素已经存在H->data[]中
    //最有一个度不为0的结点序号为h->size/2，即最后一个叶子结点的父结点
    for (int i = h->size / 2; i >= 1; --i)
        PercDownForMaxHeap(h, i);
    return ;
}

void BuildMinHeap(MinHeap h) {
    //调整h->data[]中的元素，使满足最大堆的有序性
    //这里假设所有h->size个元素已经存在H->data[]中
    //最有一个度不为0的结点序号为h->size/2，即最后一个叶子结点的父结点
    for (int i = h->size / 2; i >= 1; --i)
        PercDownForMinHeap(h, i);
    return ;
}
