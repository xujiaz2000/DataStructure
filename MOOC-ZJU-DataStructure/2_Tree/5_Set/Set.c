#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

Set CreateSet(int n) {
    //初始化集合s为包含n个元素的集合并返回
    //集合元素的val初始化为下标+1，parent初始化为-1
    Set s = (Set)malloc(sizeof(struct SetNode));
    s->data = (SetType *)malloc(n * sizeof(SetType));
    s->size = n;  //集合大小
    for (int i = 0; i < s->size; ++i) {
        s->data[i].val = i + 1;  //val初始化为下标+1
        s->data[i].parent = -1;  //parent初始化为-1
    }
    return s;
}

int PathCompression(Set s, int i) {
    //压缩，从s中下标为i的结点到其根结点的路径
    //返回s中下标为i的结点所在集合的根在s中的下标
    if (s->data[i].parent < 0)
        return i;
    else
        return s->data[i].parent = PathCompression(s, s->data[i].parent);
}

int Find(Set s, ElementType x) {
    int i;
    for (i = 0; i < s->size && s->data[i].val != x; ++i);
    if (i >= s->size) return NOTFOUND;  //未找到x，返回-1
    // for (; s->data[i].parent >= 0; i = s->data[i].parent);
    // return i;  //找到x所属集合，返回树根结点在数组s中的下标
    return PathCompression(s, i);
}

void Union(Set s, ElementType x1, ElementType x2) {
    //“按秩归并”，“按秩归并”有比树高和比规模两种，这里采用比规模（按规模归并+路径压缩比较好）
    int root1 = Find(s, x1);
    int root2 = Find(s, x2);
    if (root1 == root2) return ;  //x1和x2属于同一集合，不需要并
    if (s->data[root1].parent > s->data[root2].parent) {  //若x1所在集合较小，将其并入x2所在集合
        s->data[root2].parent += s->data[root1].parent;  //更新新集合大小
        s->data[root1].parent = root2;
    }
    else {  //若x1所在集合较大，将x1并入其所在集合
        s->data[root1].parent += s->data[root2].parent;  //更新新集合大小
        s->data[root2].parent = root1;
    }
}