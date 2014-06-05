// First_Missing_Positive.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <utility>

class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        int minPositive = getMinPositive(A, n);
        if (minPositive == -1)
            return 1;

        if (minPositive != 1)
            return 1;

        int pos = -1;
        for (int i = 0; i < n; i++)
        {
            if (A[i] <= 0)
                continue;
            pos = A[i] - minPositive;
            if (i == pos || pos >= n)
                continue;

            if (A[pos] == A[i])
                continue;

            std::swap(A[i], A[pos]);
            i--;
        }

        for (int i = 0; i < n; i++)
        {
            if (A[i] <= 0 || (i > 0 && A[i] != (A[i - 1] + 1)))
                return i + minPositive;
        }

        return minPositive + n;
    }

private:
    inline int getMinPositive(int A[], int n)
    {
        int minPositive = 0x7FFFFFFF;
        for (int i = 0; i < n; i++)
        {
            if (A[i] > 0 && A[i] < minPositive)
                minPositive = A[i];
        }

        if (minPositive == 0x7FFFFFFF)
            return -1;
        return minPositive;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = { 1, 2, 0 };
    int n = sizeof(A) / sizeof(int);

    Solution so;
    so.firstMissingPositive(A, n);

	return 0;
}

