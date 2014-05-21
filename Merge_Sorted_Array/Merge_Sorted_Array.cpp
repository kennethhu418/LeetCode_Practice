// Merge_Sorted_Array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        if (n == 0)
            return;

        if (m == 0)
        {
            memcpy(A, B, sizeof(int)*n);
            return;
        }

        int curA = m - 1, curB = n - 1, curRes = m + n - 1;

        while (curA >= 0 && curB >= 0)
        {
            if (A[curA] <= B[curB])
                A[curRes--] = B[curB--];
            else
                A[curRes--] = A[curA--];
        }

        while (curB >= 0)
            A[curRes--] = B[curB--];

        return;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

