// Search_Insert_Position.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        if (n == 0) return 0;

        if (target < A[0])   return 0;
        if (target > A[n - 1]) return n;

        int start = 0, end = n - 1, mid = 0;
        while (start < end)
        {
            mid = (start + end) / 2;

            if (target == A[mid])   return mid;
            if (target > A[mid])
            {
                start = mid + 1;
                continue;
            }

            end = mid - 1;
        }

        if (start == end)
        {
            if (A[start] == target || A[start] > target)
                return start;
            return start + 1;
        }

        //start > end
        return start;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

