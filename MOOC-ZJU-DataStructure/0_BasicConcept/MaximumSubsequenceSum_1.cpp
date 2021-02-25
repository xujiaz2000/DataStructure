#include <iostream>
#include <vector>
using namespace std;

int MaxSubseqSum1(const vector<int> &v, int &left, int &right) {
    int len = v.size();
    left = v[0]; right = v[len - 1];
    int largestSum = -1, currSum = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i; j < len; ++j) {
            currSum = 0;
            for (int k = i; k <= j; ++k)
                currSum += v[k];
            if (currSum > largestSum) {
                largestSum = currSum;
                left = v[i];
                right = v[j];
            }
        }
    }
    return max(0, largestSum);
}

int MaxSubseqSum2(const vector<int> &v, int &left, int &right) {
    int len = v.size();
    int largestSum = -1;
    left = v[0]; right = v[len - 1];
    for (int i = 0; i < len; ++i) {
        int currSum = 0;
        for (int j = i; j < len; ++j) {
            currSum += v[j];
            if (currSum > largestSum) {
                largestSum = currSum;
                left = v[i];
                right = v[j];                
            }
        }
    } 
    return max(0, largestSum);
}

int MaxSubseqSum3(const vector<int> &v, int &left, int &right) {
    //在线处理
    int largestSum = -1, currSum = 0;
    int len = v.size();
    left = v[0]; right = v[len - 1];
    int p = 0;
    for (int i = 0; i < len; ++i) {
        currSum += v[i];
        if (currSum < 0) {
            currSum = 0;
            p = i + 1;
            continue;
        }
        if (currSum > largestSum) {
            largestSum = currSum;
            left = v[p];
            right = v[i];
        }
    }
    return max(0, largestSum);
}

int main()
{
    int k;
    int left, right;
    vector<int> v;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    int largestSum = MaxSubseqSum3(v, left, right);
    cout << largestSum << " " << left << " " << right << endl;
    return 0;
}