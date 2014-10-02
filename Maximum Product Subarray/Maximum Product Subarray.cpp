// Maximum Product Subarray.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>

using namespace std;

//DP Solution
class Solution {
public:
    int maxProduct(int A[], int n) {
        if (n == 0) return 0;

        int maxProduct = A[n - 1];
        int curMax = A[n - 1], curMin = A[n - 1], curPos = n - 2, nextMax = 0, nextMin = 0;
        while (curPos >= 0){
            nextMin = min(A[curPos], min(A[curPos] * curMin, A[curPos] * curMax));
            nextMax = max(A[curPos], max(A[curPos] * curMin, A[curPos] * curMax));
            if (nextMax > maxProduct) maxProduct = nextMax;
            curMin = nextMin; curMax = nextMax;
            --curPos;
        }

        return maxProduct;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

