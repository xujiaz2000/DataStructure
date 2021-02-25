/******************************************************
 * 排序算法：
 *  - 冒泡排序：
 *  - 插入排序
 *  - 希尔排序
 *  - 堆排序
 *  - 归并排序
 *  - 快速排序
 *  - 表排序
 *  - 桶排序
 *  - 基数排序
 * 
 *  各个算法的时间复杂度、额外空间复杂度和稳定性见PPT10.4
 * 
 *  定义同一接口：void XSort(ElementType a[], int n);
 *  统一为从小到大排序
 *  （只讨论内部排序）
 ******************************************************/

#ifndef SORT_H
#define SORT_H
#include <stdbool.h>

typedef int ElementType;

void BubbleSort(ElementType a[], int n);
void InsertSort(ElementType a[], int n);
void ShellSort(ElementType a[], int n);
void HeapSort(ElementType a[], int n);
void MergeSort_R(ElementType a[], int n);
void MergeSort(ElementType a[], int n);
void QuickSort(ElementType a[], int n);
int* CreateTable(ElementType a[], int n);
void TableSort(ElementType a[], int table[], int n);
void BucketSort(ElementType a[], int n);  //没写
void LSDRadixSort(ElementType a[], int n);
void MSDRadixSort(ElementType a[], int n);

#endif 
