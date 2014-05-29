// Maximum_Subarray.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <iostream>

class Solution {
public:
    int maxSubArray(int A[], int n) {
        if (n == 0) return 0;
        if (n == 1) return A[0];

        return maxSubArray_solution2(A, 0, n - 1);
        return maxSubArray_solution1(A, n);
    }

private:
    int maxSubArray_solution1(int A[], int n)
    {
        int maxVal = 0 - 0x7FFFFFFF;
        int curPos = 0;

        //get first positive number
        while (curPos < n && A[curPos] <= 0)
        {
            if (A[curPos] > maxVal)
                maxVal = A[curPos];
            curPos++;
        }

        int start = curPos, end = curPos, curSum = 0;
        while (start < n)
        {
            curSum = 0;
            while (end < n)
            {
                if (A[end] > 0 && end > start && curSum <= 0)
                        break;

                curSum += A[end++];
                if (curSum > maxVal)
                    maxVal = curSum;
            }

            start = end;
        }

        return maxVal;
    }

    int maxSubArray_solution2(int A[], int start, int end)
    {
        if (start == end)
            return A[start];      

        if (start == end - 1)
        {
            int maxVal = A[start];
            if (A[end] > maxVal)    maxVal = A[end];
            if (A[start] + A[end] > maxVal) maxVal = A[start] + A[end];
            return maxVal;
        }

        int mid = (start + end) / 2, maxVal;
        int leftMaxVal = maxSubArray_solution2(A, start, mid - 1);
        maxVal = leftMaxVal;
        int rightMaxVal = maxSubArray_solution2(A, mid + 1, end);
        if (maxVal < rightMaxVal)   maxVal = rightMaxVal;

        //What if the maxmum sequence contains mid value
        int maxValWithMidVal = A[mid], sumWithMid = A[mid];
        for (int i = mid - 1; i >= start; i--)
        {
            sumWithMid += A[i];
            if (sumWithMid > maxValWithMidVal)
                maxValWithMidVal = sumWithMid;
        }

        sumWithMid = maxValWithMidVal;
        for (int i = mid + 1; i <= end; i++)
        {
            sumWithMid += A[i];
            if (sumWithMid > maxValWithMidVal)
                maxValWithMidVal = sumWithMid;
        }

        if (maxValWithMidVal > maxVal)
            maxVal = maxValWithMidVal;

        return maxVal;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = { -2, 1, -3 , 4, -1, 2, 1, -5, 4 };
    int n = sizeof(A) / sizeof(int);

    Solution so;
    std::cout << so.maxSubArray(A, n) << std::endl;

	return 0;
}

