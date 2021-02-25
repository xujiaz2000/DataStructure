#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LinkedHashTable.h"

int NextPrime(int n) {
    //返回大于n且不超过MAXTABLESIZE的最小素数
    //注：若找不到素数，会返回大于MAXTABLESIZE的数
    int p = n % 2 ? n + 2: n + 1;  //从大于N的下一个奇数开始
    while (p <= MAXTABLESIZE) {
        int i;
        for (i = (int)sqrt(p); i > 2; --i)
            if (!(p % i)) break;  //p不是素数
        if (i == 2) 
            break;  //for正常结束，说明p是素数
        else 
            p += 2;  //否则试探下一个奇数
    }
    return p;
}

HashTable CreateHashTable(int tableSize) {
    HashTable h = (HashTable)malloc(sizeof(struct TblNode));
    h->tableSize = NextPrime(tableSize);
    h->heads = (List)malloc(h->tableSize * sizeof(struct LNode));  //分配链表头结点数组
    //初始化表头结点
    for (int i = 0 ; i < h->tableSize; ++i) {
        h->heads[i].data[0] = '\0';
        h->heads[i].next = NULL;
    }
    return h;
}

/* 移位法 */
Index Hash(ElementType key, int tableSize) {
    unsigned int h = 0;  //散列函数值，初始化为0
    while (*key != '\0')  //位移映射
        h = (h << 5) + *key++;
    return h % tableSize;
}

Position Find(HashTable h, ElementType key) {
    Index pos = Hash(key, h->tableSize);  //初始散列位置
    Position p = h->heads[pos].next;  //从该链表的第1个结点开始
    while (p && strcmp(p->data, key))  //当未到表尾，并且Key未找到时
        p = p->next;
    return p;  //此时P或者指向找到的结点，或者为NULL
}

bool Insert(HashTable h, ElementType key) {
    Position p = Find(h, key);
    if (!p) {  //key未找到，可以插入
        Position newCell = (Position)malloc(sizeof(struct LNode));
        strcpy(newCell->data, key);
        Index pos = Hash(key, h->tableSize);  //初始散列位置
        //将newCell插入为h->heads[pos]链表的第1个结点
        newCell->next = h->heads[pos].next;
        h->heads[pos].next = newCell;
        return true;
    }
    else {  //关键字已存在
        printf("键值已存在\n");
        return false;
    }
}

void DestroyTable(HashTable h) {
    //释放每个链表的结点
    for (int i = 0; i < h->tableSize; ++i) {
        Position p = h->heads[i].next;
        while (p) {
            Position tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(h->heads);  //释放头结点数组
    free(h);         //释放散列表结点
    return ;
}
