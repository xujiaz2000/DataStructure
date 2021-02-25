#include "Polynomial.h"

int main()
{
    Polynomial p1, p2, pSum, pMult;
    p1 = PolyRead();
    p2 = PolyRead();
    pSum = PolyAdd(p1, p2);
    pMult = PolyMult(p1, p2);
    PolyPrint(pMult);
    PolyPrint(pSum);
    return 0;
}