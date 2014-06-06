// Search_for_a_Range.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> result(2, -1);

        if (n == 0) return result;

        array = A; size = n;
        
        int start = findStart(target);
        if (start == -1)
            return result;

        int end;
        //trim to end the function ASAP
        if ((start == 0 || A[start - 1] != target) && (start == n - 1 || A[start + 1] != target))
            end = start;
        else
        {
            end = findEnd(target);
            assert(end >= 0);
        }

        result[0] = start; result[1] = end;
        return result;
    }

private:
    int*    array;
    int      size;

    inline int findStart(int target)
    {
        int start = 0, end = size - 1, mid = -1;
        while (start < end)
        {
            mid = (start + end) / 2;
            if (target < array[mid])
            {
                end = mid - 1;  continue;
            }
            if (target > array[mid])
            {
                start = mid + 1; continue;
            }

            if (mid == start || array[mid - 1] != target)
                return mid;

            end = mid - 1;
        }

        if (start == end)
        {
            if (array[start] == target)
                return start;
            return -1;
        }

        return -1;
    }

    inline int findEnd(int target)
    {
        int start = 0, end = size - 1, mid = -1;
        while (start < end)
        {
            mid = (start + end) / 2;
            if (target < array[mid])
            {
                end = mid - 1;  continue;
            }
            if (target > array[mid])
            {
                start = mid + 1; continue;
            }

            if (array[mid + 1] != target)
                return mid;

            start = mid + 1;
        }

        if (start == end)
        {
            if (array[start] == target)
                return start;
            return -1;
        }

        return -1;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

