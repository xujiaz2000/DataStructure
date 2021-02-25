#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HashTable.h"

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
    //创建并返回一个大小为tableSize的空的哈希表
    HashTable h = (HashTable)malloc(sizeof(struct TblNode));
    h->tableSize = NextPrime(tableSize);  //保证散列表最大长度是素数
    h->cells = (Cell *)malloc(h->tableSize * sizeof(Cell));  //声明单元数组
    //初始化单元状态为“空单元”
    for (int i = 0; i < h->tableSize; ++i)
        h->cells[i].info = Empty;
    return h;
}

/* 待改，暂且：h(key) = key % 11 */
Position Hash(ElementType key, int tableSize) {
    return key % 11;
}

Position Find(HashTable h, ElementType key) {
    //冲突处理方法：平方探测法
    Position currPos, newPos;
    int cNum = 0;  //记录冲突次数

    currPos = newPos = Hash(key, h->tableSize);  //初始散列位置
    //当该位置的单元非空，并且不是要找的元素时，发生冲突
    while (h->cells[newPos].info != Empty && h->cells[newPos].data != key) {
        //字符串类型的关键词需要 strcmp 函数!!
        //统计冲突次数，并判断奇偶次
        if (++cNum % 2) {  //奇数次冲突
            newPos = currPos + (cNum + 1) * (cNum + 1) / 4;  //增量为+[(cNum+1)/2]^2
            if (newPos >= h->tableSize)
                newPos = newPos % h->tableSize;  //调整为合法地址
        }
        else {  //偶数次冲突
            newPos = currPos - cNum * cNum / 4;  //增量为-(cNum/2)^2
            while (newPos < 0)
                newPos += h->tableSize;  //调整为合法地址
        }
    }
    return newPos;  //此时newPos或者是key的位置，或者是一个空单元的位置（表示找不到）
}

bool Insert(HashTable h, ElementType key) {
    Position pos = Find(h, key);
    if (h->cells[pos].info != Legitimate) {  //如果这个单元没有被占，说明Key可以插入在此
        h->cells[pos].data = key;
        //字符串类型的关键词需要 strcpy 函数!!
        h->cells[pos].info = Legitimate;  //标记这个单元已被合法占用
        return true;
    }
    else {
        printf("key已存在");
        return false;
    }
}


