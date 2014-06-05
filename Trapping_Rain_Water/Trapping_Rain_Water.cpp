// Trapping_Rain_Water.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <algorithm>

using namespace std;

#define MIN_WATER_HEIGHT  -1

class Solution {
public:
    int trap(int A[], int n) {
        if (n < 3)  return 0;

        int totalWater = 0;
        int highestPoint1 = -1, highestPoint2 = -1, highestPoint;

        highestPoint1 = findHighestPoint(A, n, 0);
        assert(highestPoint1 < n && highestPoint1 >= 0);
        while (highestPoint1 < n)
        {
            highestPoint2 = findHighestPoint(A, n , highestPoint1 + 1);
            if (highestPoint2 < 0)
                break;

            highestPoint = std::min(A[highestPoint1], A[highestPoint2]);
            for (int i = highestPoint1; i <= highestPoint2; i++)
            {
                if (A[i] < highestPoint)
                    totalWater += (highestPoint - A[i]);
            }
                

            highestPoint1 = highestPoint2;
        }

        return totalWater;
    }

private:
    inline int findHighestPoint(int A[], int n, int start)
    {
        if (start >= n)
            return -1;

        int left = 0;
        int right = 0;

        while (start < n)
        {
            left = start > 0 ? A[start - 1] : MIN_WATER_HEIGHT;
            right = (start == n - 1) ? MIN_WATER_HEIGHT : A[start + 1];
            if (A[start] >= left && A[start] > right)
                return start;
            start++;
        }

        return -1;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    int n = sizeof(A) / sizeof(int);

    Solution so;
    so.trap(A, n);
	return 0;
}

