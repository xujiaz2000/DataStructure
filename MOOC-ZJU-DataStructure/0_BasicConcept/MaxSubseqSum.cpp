#include <iostream>
#include <vector>
using namespace std;

int MaxSubseqSum(const vector<int> &v) {
    //在线处理
    int largestSum = -1, currSum = 0;
    int len = v.size();
    for (int i = 0; i < len; ++i) {
        currSum += v[i];
        if (currSum < 0) {
            currSum = 0;
            continue;
        }
        if (currSum > largestSum) {
            largestSum = currSum;
        }
    }
    return max(0, largestSum);
}

int main()
{
    int k;
    vector<int> v;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    int largestSum = MaxSubseqSum(v);
    cout << largestSum<< endl;
    return 0;
}