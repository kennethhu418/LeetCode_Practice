// Next_Permutation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using std::vector;
using std::swap;

class Solution {
public:
    void nextPermutation(vector<int> &nums) {
        int n = nums.size();
        if (n < 2)  return;
        if (n == 2)
        {
            swap(nums[0], nums[1]);
            return;
        }

        int firstDecIndex = getFirstDecreaseNumFromBack(nums);
        if (firstDecIndex == -1)
        {
            ReverseArray(nums, 0, n - 1);
            return;
        }

        ReverseArray(nums, firstDecIndex + 1, n - 1);

        for (int i = firstDecIndex + 1; i < n; i++)
        {
            if (nums[i] > nums[firstDecIndex])
            {
                swap(nums[i], nums[firstDecIndex]);
                return;
            }
        }

        assert(0);
    }

private:
    inline int getFirstDecreaseNumFromBack(const vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
            return -1;

        for (int i = n - 2; i >= 0; i--)
        {
            if (nums[i] < nums[i + 1])
                return i;
        }

        return -1;
    }

    inline void ReverseArray(vector<int> &nums, int start, int end)
    {
        while (start < end)
        {
            swap(nums[start], nums[end]);
            start++; end--;
        }
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = {1, 2, 3, 4};
    vector<int> nums(A, A + sizeof(A)/sizeof(int));

    Solution    so;
    so.nextPermutation(nums);

	return 0;
}

