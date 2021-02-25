/******************************************************
 * 并查集：采用数组存储形式
 *  - 功能：集合并、查某元素属于什么集合
 ******************************************************/

#ifndef SET_H
#define SET_H

/* 数据对象集 */
typedef int ElementType;
typedef struct {
    ElementType val;
    int parent;  //表示当前结点的父亲在Set数组中的下标
} SetType;

typedef struct SetNode *Set;
struct SetNode {
    SetType *data;  //集合，指向SetType类型的数组
    int size;  //集合大小
};

#define NOTFOUND -1  //查找失败标记

/* 操作集 */
Set CreateSet(int n);
int Find(Set s, ElementType x);
void Union(Set s, ElementType x1, ElementType x2);

#endif
