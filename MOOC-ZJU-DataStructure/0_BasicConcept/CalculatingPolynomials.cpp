//给定 f(x) = 1 + x + x^2/2 + ... + x^i/i + x^100/100，用两种方法求f(1.1)，并比较计时
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

double f1(int n, double a[], double x) {
    //f1(x) = a0 + a1x^1 + a2x^2 + ... + anx^n
    double result = a[0];
    for (int i = 1; i <= n; ++i)
        result += a[i] * pow(x, i);
    return result;
}

double f2(int n, double a[], double x) {
    //f2(x) = a0 + x(a1 + x(a2 + ... + x(an-1 + xan)))
    double result = a[n];
    for (int i = n - 1; i >= 0; --i)
        result = a[i] + x * result;
    return result;
}

int main()
{
    clock_t start, stop;
    const int kMaxK = 1e3;
    const int kMaxN = 101;
    double a[kMaxN] = {0};
    double x = 1.1;
    for (int i = 1; i < kMaxN; ++i)
        a[i] = 1.0 / i;
    
    start = clock();
    double result1 = f1(kMaxN - 1, a, x);
    for (int i = 0; i < kMaxK; ++i)
        f1(kMaxK - 1, a, x);
    stop = clock();
    double duration1 = (double)(stop - start) / CLK_TCK / kMaxK;
    cout << "result1 = " << result1 << endl << "duration1 = " << duration1 << endl;

    start = clock();
    double result2 = f1(kMaxN - 1, a, x);
    for (int i = 0; i < kMaxK; ++i)
        f2(kMaxK - 1, a, x);
    stop = clock();
    double duration2 = (double)(stop - start) / CLK_TCK / kMaxK;
    cout << "result2 = " << result2 << endl << "duration2 = " << duration2 << endl;

    return 0; 
}
