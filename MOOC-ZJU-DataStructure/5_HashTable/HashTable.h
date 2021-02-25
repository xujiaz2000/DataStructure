/******************************************************
 * 散列表（哈希表）
 *      - 数据对象集："Name-Attribute"对的集合
 *      - 操作集：...
 *  - 散列表的两项工作：
 *      - 计算位置
 *      - 解决冲突
 *  - 散列（Hashing）：以关键字 key 为自变量，通过一个函数 h，计算出数据对象的存储地址 h(key)
 *  - 冲突：不同关键字可能会散列到同一地址，需要解决冲突
 * 
 *  - T查询 = T插入 = T删除 = O(1)
 *  - 再散列：装填因子过大会使得查找效率下降，故当装填因子过大时，加倍扩大散列表
 * 
 *  散列函数的构造方法：
 *  - 数字关键字
 *      1. 直接定址法：h(key) = a * key - b
 *      2. 除留余数法：h(key) = key % p ，为分布均匀这里p取素数
 *      3. 数字分析法：取比较随机的位作为key，计算h(key)
 *      4. 折叠法
 *      5. 平法取中法
 *  - 字符关键字
 *      1. ASCII码加和法：h(key) = (Σkey[i]) mod tableSize
 *      2. 移位法：h(key) = sigma of key[n - i + 1] * 32^i with i = 0 to n-1 mod tableSize（看作32进制）
 * 
 *  冲突处理方法
 *  - 开放地址法：换个位置
 *      1. 线性探测法
 *      2. 平方探测法
 *      3. 双散列探测法
 *  - 链地址法：同一位置的冲突组织在一起
 *      1. 分离链接法  
 * 
 * 本例：
 *  - key类型：数字
 *  - 散列函数的构造方法：除留余数法
 *  - 冲突处理方法：平方探测法
 ******************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdbool.h>

/* 数据对象集 */
#define MAXTABLESIZE 100000 /* 允许开辟的最大散列表长度 */
typedef int ElementType;    /* 关键词类型用整型 key的类型 */
typedef int Index;          /* 散列地址类型 h(key)的类型 */
typedef Index Position;     /* 数据所在位置与散列地址是同一类型 */
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum {Legitimate, Empty, Deleted} EntryType;

typedef struct HashEntry Cell;  //散列表单元类型
struct HashEntry {
    ElementType data;  //存储元素
    EntryType info;    //单元状态
};

typedef struct TblNode *HashTable;  //散列表类型
struct TblNode {  //散列表结点定义
    int tableSize;  //表的最大长度
    Cell *cells;    //存放散列单元数据的数组
};

/* 操作集 */
HashTable CreateHashTable(int tableSize);
Position Find(HashTable h, ElementType key);
bool Insert(HashTable h, ElementType key);


#endif
