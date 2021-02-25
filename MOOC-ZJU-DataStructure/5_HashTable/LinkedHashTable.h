/******************************************************
 * 散列表（哈希表）
 *  - key类型：字符串
 *  - 散列函数的构造方法：移位法
 *  - 冲突处理方法：分离链接法
 ******************************************************/

#ifndef LINKEDHASHTABLE_H
#define LINKEDHASHTABLE_H
#include <stdbool.h>

/* 数据对象集 */
#define MAXTABLESIZE 10000                  //允许开辟的最大散列表长度
#define KEYLENGTH 15                        //关键词字符串的最大长度
typedef char ElementType[KEYLENGTH + 1];    //关键词类型用字符串
typedef int Index;                          //散列地址类型

//单链表的定义
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType data;
    PtrToLNode next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;  //散列表类型
struct TblNode {    //散列表结点定义
    int tableSize;  //表的最大长度
    List heads;     //指向链表头结点的数组
};

/* 操作集 */
HashTable CreateHashTable(int tableSize);
Position Find(HashTable h, ElementType key);
bool Insert(HashTable h, ElementType key);
void DestroyTable(HashTable h);

#endif
