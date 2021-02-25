#include <stdio.h>
#include <stdlib.h>
#include "Polynomial.h"

/* 比较指数大小，在多项式相加函数中被调用 */
int Compare(int expon1, int expon2) {
    if (expon1 == expon2)
        return 0;
    return (expon1 > expon2 ? 1: -1);
}

/* 扩展多项式，添加至链表最后 */
void Attach(int c, int e, PtrToNode *rear) {
    PtrToNode ptrN = (PtrToNode)malloc(sizeof(struct PolyNode));
    ptrN->coef = c;
    ptrN->expon = e;
    ptrN->next = NULL;
    (*rear)->next = ptrN;
    *rear = ptrN;
}

/* 多项式相加 */
Polynomial PolyAdd(Polynomial p1, Polynomial p2) {
    int sum;
    PtrToNode front, rear;  //分别指向结果的首结点和尾结点
    PtrToNode tmp;
    front = (PtrToNode)malloc(sizeof(struct PolyNode));  //为方便插入，先创建一个临时空结点作为结果多项式的链表头
    rear = front;
    while (p1 && p2) {  //遍历完p1或p2后结束循环
        switch (Compare(p1->expon, p2->expon)) {
        case 1:
            Attach(p1->coef, p1->expon, &rear);
            p1 = p1->next;
            break;
        case -1:
            Attach(p2->coef, p2->expon, &rear);
            p2 = p2->next;
            break;
        case 0:
            sum = p1->coef + p2->coef;
            if (sum)
                Attach(sum, p1->expon, &rear);
            p1 = p1->next;
            p2 = p2->next;
            break;
        }
    }
    for (; p1; p1 = p1->next) Attach(p1->coef, p1->expon, &rear);
    for (; p2; p2 = p2->next) Attach(p2->coef, p2->expon, &rear);
    tmp = front;
    front = front->next;
    free(tmp);
    return front;
}

/* 单项式乘多项式，在多项式相乘函数中被调用 */
Polynomial OneMultPoly(PtrToNode ptrN, Polynomial ptrP) {
    PtrToNode front, rear, tmp;
    front = rear = (PtrToNode)malloc(sizeof(struct PolyNode));
    while (ptrP) {
        Attach(ptrN->coef * ptrP->coef, ptrN->expon + ptrP->expon, &rear);
        ptrP = ptrP->next;
    }
    tmp = front;
    front = front->next;
    free(tmp);
    return front;
}

/* 多项式相乘 */
Polynomial PolyMult(Polynomial p1, Polynomial p2) {
    Polynomial result = OneMultPoly(p1, p2);  //先用p1的第一项乘p2，暂最为结果
    p1 = p1->next;
    while (p1) {  //将乘法转换为加法运算（将p1当前项乘p2多项式，再加到结果多项式里）
        Polynomial tmp1 = OneMultPoly(p1, p2);
        Polynomial tmp2 = PolyAdd(result, tmp1);
        PolyFree(tmp1);
        PolyFree(result);
        result = tmp2;
        p1 = p1->next;
    }
    return result;
}

/* 多项式输入，输入格式：（项数 系数 指数 系数 指数 ...） */
Polynomial PolyRead() {
    int n, c, e;
    PtrToNode front, rear, tmp;
    front = rear = (PtrToNode)malloc(sizeof(struct PolyNode));  //为方便插入，先创建一个临时空结点作为结果多项式的链表头
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &c, &e);
        Attach(c, e, &rear);
    }
    tmp = front;
    front = front->next;
    free(tmp);
    return front;
}

/* 多项式输出，输出格式：（系数 指数 系数 指数 ...） */
void PolyPrint(Polynomial p) {
    if (!p) {
        printf("0 0\n");
        return ;
    }
    int flag = 1;
    while (p) {
        if (flag)
            flag = 0;
        else
            printf(" ");
        printf("%d %d", p->coef, p->expon);
        p = p->next;
    }
    printf("\n");
    return ;
}

/* 释放多项式 */
void PolyFree(Polynomial p) {
    PtrToNode tmp;
    while (p) {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return ;
}