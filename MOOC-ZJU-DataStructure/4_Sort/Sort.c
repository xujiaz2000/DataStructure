#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

void Swap(ElementType *a, ElementType *b) {
    ElementType tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 冒泡排序 
 *  - 稳定
 *  - 复杂度分析：
 *      - 最好情况：T = O(N)
 *      - 最坏情况：T = O(N^2)
 *  - 优势在于适用于单向链表
 */
void BubbleSort(ElementType a[], int n) {
    for (int p = n - 1; p > 0; --p) {  //p是最后一个乱序元素的下标
        bool flag = 0;  //标记一趟冒泡后是否有元素交换
        for (int i = 0; i < p; ++i) {
            if (a[i] > a[i + 1]) {
                Swap(&a[i], &a[i + 1]);
                flag = 1;  //发生了交换
            }
        }
        if (flag == 0)  //若全程无交换，说明已经有序
            break;  //算法结束
    }
    return ;
}

/* 插入排序
 *  - 稳定
 *  - 前有序，后无序，每次取出无序序列的第一个元素，将其插入到有序序列正确位置中
 *  - 复杂度分析：
 *      - 最好情况：T = O(N)
 *      - 最坏情况：T = O(N^2)
 *  - 每次交换相邻元素消去一个逆序对，插入排序 T(N, I) = O(N + I) ，I是逆序对数
 *  - 任何仅以交换相邻两元素来排序的算法，其平均时间复杂度为O(N^2)
 *  - 如果序列基本有序，插入排序简单且高效
 */
void InsertSort(ElementType a[], int n) {
    for (int p = 1; p < n; ++p) {  //前有序，后无序，p是第一个无序元素的下标
        ElementType tmp = a[p];  //当前待插入元素内容
        int i;  //i是元素tmp应该在的位置的下标
        for (i = p; i - 1 >= 0 && a[i - 1] > tmp; --i)
            a[i] = a[i - 1];  //移出空位
        a[i] = tmp;  //新牌落位
    }
    return ;
}

/* 希尔排序
 *  - 不稳定
 *  - 算法
 *      - 定义增量序列：D_M > D_M-1 > ... > D_1 = 1（增量序列相邻元素应该互质）
 *      - 对每个D_k进行“D_k间隔”排序
 *  - “D_k间隔”有序的序列，在执行“D_k-1间隔”排序后，“D_k间隔”仍然有序
 *  - 复杂度分析（Sedgewick增量序列）：
 *      - 平均情况：T = O(N^(7/6))
 *      - 最坏情况：T = O(N^(4/3))
 */
void ShellSort(ElementType a[], int n) {
    //希尔排序 - 用Sedgewick增量序列
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};  //这里只列出一小部分增量
    int si;
    for (si = 0; Sedgewick[si] >= n; ++si);  //初始的增量Sedgewick[Si]不能超过待排序列长度

    for (int D = Sedgewick[si]; D > 0; D = Sedgewick[++si])  //希尔增量序列
        for (int p = D; p < n; ++p) {  //插入排序
            ElementType tmp = a[p];
            int i;
            for (i = p; i - D >= 0 && a[i - D] > tmp; i -= D)
                a[i] = a[i - D];
            a[i] = tmp;
        }
    return ;
}

/* 堆排序
 *  - 不稳定
 *  - 选择排序：前有序，后无序，每次从无序序列中找出最小者，与有序序列尾后元素交换
 *  - 堆排序：是对选择排序的改进
 *      - 法一：将数组建成最小堆，然后不断DeleteMin至临时数组，最后再复制回。
 *          - 优：O(N^2)->O(NlogN)
 *          - 劣：需要额外O(N)空间，并且复制元素需要时间
 *      - 法二：将数组建成最大堆，然后不断交换根结点与最后一个叶子节点
 *          - T = O(NloglogN)，稍优于 O(NlogN)
 *  - 堆排序给出了最佳平均时间复杂度，但是实际效果不如用Sedgewick增量序列的希尔排序
 *  - 适用于：如果在排序时需找出（n个）最大或最小的元素，堆排序较为方便。
 *           此外如果要排序的数据会自动更新，且需要在每次更新后找到最大或最小元素，堆排序也是一个不错的选择。
 */
void PercDown(ElementType a[], int p, int n) {
    //将n个元素的数组以a[p]为根的子堆调整为最大堆（假设左右子树已为最大堆）
    //代码解释见Heap部分代码
    ElementType x = a[p];
    //p用来记录x应该在的位置下标
    while (p * 2 + 1 < n) {  //若有左孩子
        p = 2 * p + 1;
        if (p + 1 < n && a[p + 1] > a[p])
            ++p;
        if (x >= a[p]) {
            p = (p - 1) / 2;
            break;
        }
        a[(p - 1) / 2] = a[p];
    }
    a[p] = x;
    return ;
}

/* 堆排序 */
void HeapSort(ElementType a[], int n) {
    //建立最大堆
    for (int p = n / 2 - 1; p >= 0; --p)
        PercDown(a, p, n);

    //交换堆顶元素和无序部分的尾元素
    for (int p = n - 1; p > 0; --p) { //p是无序部分的尾元素下标
        Swap(&a[0], &a[p]);
        PercDown(a, 0, p);
    }

    return ;
}

/* 归并排序
 *  - 稳定
 *  - 分而治之
 *  - 复杂度分析
 *      - 不分情况好坏：T(N) = T(N / 2) + T(N / 2) + O(N) = O(NlogN)
 *  - 优：最好，最坏复杂度都是O(NlogN)；稳定
 *  - 劣：需要额外O(N)的空间，所以一般不用于内排序，适用于外排序
 */
void Merge(ElementType a[], ElementType tmp[], int l, int m, int r) {
    //序列分为前后，l为前序列首元素下标，m为后序列首元素下标，r为全序列尾后元素下标
    //如果只在Merge中声明临时数组tmp[]，会在递归时不断malloc和free，造成浪费
    int i = 0;  //tmp[]的下标
    int pl = l, pr = m;

    while (pl < m && pr < r) {  //不断取出较小者放入tmp[]
        if (a[pl] <= a[pr])
            tmp[i++] = a[pl++];
        else
            tmp[i++] = a[pr++];
    }
    while (pl < m)
        tmp[i++] = a[pl++];  //直接复制左边剩下的
    while (pr < r)
        tmp[i++] = a[pr++];  //直接复制右边剩下的

    for (i = 0, pl = l; i < r - l; ++i, ++pl)
        a[pl] = tmp[i];  //将有序的tmp[]复制回a[]

    return ; 
}

void MSort(ElementType a[], ElementType tmp[], int l, int r) {
    //l：首元素下标，r：尾后元素下标
    if (r - l > 1) {  //反之，若序列只有一个元素，其自然有序无需排序
        int m = l + (r - l) / 2;
        MSort(a, tmp, l, m);        /* 递归解决左边 */ 
        MSort(a, tmp, m, r);        /* 递归解决右边 */  
        Merge(a, tmp, l, m, r);     /* 合并两段有序序列 */ 
    }
    return ;
}

/* 归并排序的递归算法 */
void MergeSort_R(ElementType a[], int n) {
    ElementType *tmp = (ElementType *)malloc(n * sizeof(ElementType));
    if (tmp != NULL) {
        MSort(a, tmp, 0, n);
        free(tmp);
    }
    else
        printf("归并排序失败，空间不足");
    return ;
}

void Merge1(ElementType a[], ElementType tmp[], int l, int m, int r) {
    //Merge1()与Merge()的区别在于前者最后不讲tmp[]转移会a[]
    //在非递归实现的归并排序中可以节省时间
    int i = l;  //tmp[]的下标
    int pl = l, pr = m;

    while (pl < m && pr < r) {  //不断取出较小者放入tmp[]
        if (a[pl] <= a[pr])
            tmp[i++] = a[pl++];
        else
            tmp[i++] = a[pr++];
    }
    while (pl < m)
        tmp[i++] = a[pl++];  //直接复制左边剩下的
    while (pr < r)
        tmp[i++] = a[pr++];  //直接复制右边剩下的

    return ; 
}

void MergePass(ElementType a[], ElementType tmp[], int n, int len) {
    //n：完整序列长度，len：当前有序子列的长度
    //每次MergePass都会将待排序序列转移到对立数组中，即a[]->tmp[]或tmp[]->a[]
    //故偶数次MergePass可以保证待排序序列仍在a[]中
    int i;
    for (i = 0; i <= n - 2 * len; i += 2 * len) {
        //i遍历每一对（2个）有序子列的首元素
        //剩下至多两对另外处理
        Merge1(a, tmp, i, i + len, i + 2 * len);
    }
    if (i + len < n)  //若最后剩下两对
        Merge1(a, tmp, i, i + len, n);
    else //若最后只剩下一对
        for (; i < n; ++i) tmp[i] = a[i];
    
    return ;
}

/* 归并排序的非递归算法 */
void MergeSort(ElementType a[], int n) {
    ElementType *tmp = (ElementType *)malloc(n * sizeof(ElementType));
    int len = 1;  //初始化有序子列长度为1
    if (tmp != NULL) {
        while (len < n) {
            MergePass(a, tmp, n, len);
            len *= 2;
            MergePass(tmp, a, n, len);  //把序列倒回a[]
            len *= 2;
        }
        free(tmp);
    }
    else 
        printf("归并排序失败，空间不足");

    return ;
}


/* 快速排序
 *  - 不稳定
 *  - 分而治之
 *      1. 从a[]中选一个主元（pivot）
 *      2. 利用主元将a[]分成2个独立的子集，前子集都比主元小，后子集都比主元大
 *      3. 对前后子集进行第1步和第2步
 *  - ”快速“：每次子集划分后主元最终位置确定，不再改变
 *  - 复杂度分析：
 *      - 最好情况（主元每次正好中分）：T(N) = T(N/2)+T(N/2)+O(N) = O(NlogN)
 *      - 最坏情况（主元每次位于两边）：T(N) = N*O(N) = O(N^2)
 *  - 快排存在的问题及解决：
 *      - 问题：用递归，开销大，以至于对小规模的数据（如N<100）可能还不如插入排序快
 *      - 解决：当递归的数据规模充分小时，停止递归，直接调用简单排序。在程序中定义一个cutoff阈值
 *  - 注：
 *      - 合理地选取主元可以使得复杂度降低，比如：取头、中、尾的中位数
 *      - 子集划分期间如果左右指针遇到等于pivot额元素，应该停下来交换。（因为此时，当所有元素相同时，子集划分近似对半）
 */

#define CUTOFF 100  //待排序列规模小于CUTOFF，调用简单排序

/* 取头、中、尾的中位数 */
ElementType Median3(ElementType a[], int l, int r) {
    //l：首元素下标，r：尾后元素下标
    //返回取头、中、尾的中位数
    //并按从小到大顺序放置在数组的首、尾前和尾的位置
    //这样的话，子集划分范围变为：a[l + 1] ~ a[r - 3]
    int m = l + (r - l) / 2;
    r -= 1;  //令r为尾元素下标
    if (a[l] > a[m])
        Swap(&a[l], &a[m]);
    if (a[l] > a[r])
        Swap(&a[l], &a[r]);
    if (a[m] > a[r])
        Swap(&a[m], &a[r]);
    // a[l] <= a[m] <= a[r] 
    Swap(&a[m], &a[r - 1]);  //将pivot藏到后面，方便子集划分
    return a[r - 1];  //返回pivot
}

void QSort(ElementType a[], int l, int r) {
    //核心递归函数
    //l：首元素下标，r：尾后元素下标
    //注意：CUTOFF不能小于3，否则，由于j = r - 2后while (a[--j] > pivot)下标越界
    if (r - l < CUTOFF)  //若待排序列规模小于CUTOFF，调用简单排序
        InsertSort(a + l, r - l);
    else {  //若序列元素充分多，进入快排
        ElementType pivot = Median3(a, l, r);
        int i = l, j = r - 2; 
        for ( ; ; ) {
            while (a[++i] < pivot) ;
            while (a[--j] > pivot) ;
            if (i < j)
                Swap(&a[i], &a[j]);
            else
                break;
        }
        Swap(&a[i], &a[r - 2]);  //将pivot放到正确的位置
        QSort(a, l, i);
        QSort(a, i + 1, r);
    }
    return ;
}

/* 快速排序 */
void QuickSort(ElementType a[], int n) {
    //统一接口
    QSort(a, 0, n);
    return ;
}

/* 表排序
 *  - 适用于：待排元素本身是一个庞大的结构体，其移动时间不可忽略
 *  - 表排序属于间接排序：不移动数据本身，只移动指针（它定义一个指针数组，称为“表”（table））
 */
int* CreateTable(ElementType a[], int n) {
    //间接排序
    //返回table[]，其中table[i]的值是应该在下标i位置的元素当前的下标
    //利用插入排序实现，就在比较元素和交换元素时用到table[]
    int *table  = (int *)malloc(n * sizeof(ElementType));
    //表的初始化
    for (int i = 0; i < n; ++i)
        table[i] = i;

    for (int p = 1; p < n; ++p) {
        ElementType tmp = a[p];
        int i;
        for (i = p; i - 1 >= 0 && a[table[i - 1]] > tmp; --i)
            table[i] = table[i - 1];
        table[i] = p;
    }
    return table;
}

void TableSort(ElementType a[], int table[], int n) {
    //物理排序
    //n个数组的排列由若干个独立的环组成
    //最好情况：初始即有序
    //最坏情况：有N/2个环，每个环含2个元素，需要3N/2次元素移动
    // T = O(mN)，m是每个元素复制的时间
    //图解见PPT10-2
    for (int i = 0; i < n; ++i) {
        if (table[i] == i) continue;  //第i个元素已有序
        ElementType tmp = a[i];
        int tmpI = i, tableI = table[i];
        while (tableI != i) {  //若环未结束
            a[tmpI] = a[tableI];
            table[tmpI] = tmpI;
            tmpI = tableI;
            tableI = table[tmpI];
        }
        a[tmpI] = tmp;
        table[tmpI] = tmpI;
    }
    return ;
}

/* 桶排序 */
void BucketSort(ElementType a[], int n) {
    //假设有n个学生，m个成绩，排序
    //开一个大小为m的链表数组，遍历a[]，将其插入到链表数组中；遍历链表数组，按序放回a[]
    //T = (M + N)  ————线性时间
    //劣：M >> N 时空间时间开销都很大
}

/* 基数排序（多关键字的排序）
 *  - 稳定
 *  - 两种方法
 *      1. MST：主位优先：先按主位入桶，再在桶内按次位排序（递归）
 *      2. LST：次位优先：先按次位入桶，按顺序出桶，此时次位有序，再按主位入桶，按顺序出桶，从而主位亦有序
 *  - 这里的主次位可以指：整数的高低位，即先按个位排序，再按十位排序...
 */

//假设元素最多有MaxDigit个关键字，基数全是同样的Radix
#define maxDigit 4
#define radix 10

//桶元素结点
typedef struct Node *PtrToNode;
struct Node {
    int key;
    PtrToNode next;
};

//桶头结点
struct HeadNode {
    PtrToNode head, tail;
};
typedef struct HeadNode Bucket[radix];  //基数个桶

int GetDigit(int x, int d) {
    //返回元素x的第d次位，默认次位d=1，主位d<=maxDigit
    //e.g. GetDigit(1234, 3) -> 2
    int res;
    for (int i = 0; i < d; ++i) {
        res = x % radix;
        x /= radix;
    }
    return res;
}

/************************* 基数排序 - 次位优先 *************************/
/* 基数排序：次位优先 */
void LSDRadixSort(ElementType a[], int n) {
    // T(N) = O(maxDigit*(n + radix))，若radix较小，T ~ O(N)
    PtrToNode lst = NULL;
    Bucket b;
    //初始化每个桶为空链表
    for (int i = 0; i < radix; ++i)
        b[i].head = b[i].tail = NULL;
    //将原始序列逆序存入初始链表list
    for (int i = 0; i < n; ++i) {
        PtrToNode tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->key = a[i];
        tmp->next = lst;
        lst = tmp;
    }
    //下面开始排序
    for (int d = 1; d <= maxDigit; ++d) {  //对数据的每一位循环处理
        //下面是分配的过程
        PtrToNode p = lst;
        while (p) {
            int di = GetDigit(p->key, d);  //获得当前元素的当前位数字
            //从lst中摘除p
            PtrToNode tmp = p; p = p->next;  
            tmp->next = NULL;
            //插入b[di]号桶尾
            if (b[di].head == NULL)
                b[di].head = b[di].tail = tmp;
            else {
                b[di].tail->next = tmp;
                b[di].tail = tmp;
            }
        }
        //下面是收集的过程
        lst = NULL;
        for (int di = radix - 1; di >= 0; --di) {  //将每个桶的元素顺序收集入lst
            if (b[di].head) {  //如果桶不为空
                //整桶插入lst表头
                b[di].tail->next = lst;
                lst = b[di].head;
                b[di].head = b[di].tail = NULL;  //清空桶
            }
        }
    }
    //将lst倒入a[]并释放空间
    for (int i = 0; i < n; ++i) {
        PtrToNode tmp = lst;
        a[i] = tmp->key;
        lst = lst->next;
        free(tmp);
    }
    return ;
}
/*************************   次位优先 结束    *************************/

/************************* 基数排序 - 次位优先 *************************/
void MSD(ElementType a[], int l, int r, int d) {
    //核心递归函数，对a[l]...a[r]的第d位数进行排序
    Bucket b;
    PtrToNode lst = NULL;

    if (d == 0) return ; //递归终止条件

    //初始化每个桶为空链表
    for (int i = 0; i < radix; ++i) 
        b[i].head = b[i].tail = NULL;
    //将原始序列逆序存入初始链表lst
    for (int i = l; i  < r; ++i) {  
        PtrToNode tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->key = a[i];
        tmp->next = lst;
        lst = tmp;
    }
    //下面分配的过程
    PtrToNode p = lst;
    while (p) {
        int di = GetDigit(p->key, d);  //获得当前元素的当前位数字
        //从lst中摘除
        PtrToNode tmp = p; p = p->next;
        //插入b[di]号桶
        tmp->next = b[di].head;
        b[di].head = tmp;
        if (b[di].head == NULL) b[di].tail = tmp;
    }
    //下面是收集的过程
    int i, j;
    i = j = l;  //i, j记录当前要处理的a[]的左右端下标
    for (int di = 0; di < radix; ++di) {  //对于每个桶
        //若桶非空的桶整桶倒入A[], 递归排序
        if (b[di].head) {  
            p = b[di].head;
            while (p) {
                PtrToNode tmp = p;
                p = p->next;
                a[j++] = tmp->key;
                free(tmp);
            }
            MSD(a, i, j, d - 1);  //递归对该桶数据排序, 位数减1
            i = j;  //i为下一个桶对应的a[]左端
        }
    }
    return ;
}

/* 基数排序：主位优先 */
void MSDRadixSort(ElementType a[], int n) {
    //统一接口
    MSD(a, 0, n, maxDigit);
    return ;
}

/*************************   次位优先 结束    *************************/
