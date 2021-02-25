#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sort.h"

#define ARRAY_NUM 10
int a[ARRAY_NUM] = {1, 6, 5, 0, 3, 2, 7, 4, 8, 9};

/* fake shuffle */
void Shuffle(ElementType a[], int n) {
    int b[ARRAY_NUM] = {1, 6, 5, 0, 3, 2, 7, 4, 8, 9};
    for (int i = 0; i < ARRAY_NUM; ++i)
        a[i] = b[i];
    return ;
}

void Print(ElementType a[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);
    putchar(10);
    return ;
}

int main() 
{
    BubbleSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    InsertSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    ShellSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    HeapSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    MergeSort_R(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    MergeSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    QuickSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    int *table = CreateTable(a, ARRAY_NUM); Print(table, ARRAY_NUM); TableSort(a, table, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    LSDRadixSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);
    MSDRadixSort(a, ARRAY_NUM); Print(a, ARRAY_NUM); Shuffle(a, ARRAY_NUM);;

    return 0;
}