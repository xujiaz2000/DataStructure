/******************************************************
 * 多项式链表顺序：按指数由大往小
 ******************************************************/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

/* 数据对象集 */
typedef struct PolyNode *Polynomial; 
typedef struct PolyNode *PtrToNode;
struct PolyNode {
    int coef;   //系数
    int expon;  //指数
    PtrToNode next;
};

/* 操作集 */
void Attach(int c, int e, PtrToNode *rear);
Polynomial PolyAdd(Polynomial p1, Polynomial p2);
Polynomial PolyMult(Polynomial p1, Polynomial p2);
Polynomial PolyRead();
void PolyPrint(Polynomial p);
void PolyFree(Polynomial p);

#endif