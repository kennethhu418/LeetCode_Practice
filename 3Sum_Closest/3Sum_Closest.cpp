// 3Sum_Closest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_UNSIGNED_INT  0x6FFFFFFF

using std::vector;

class Solution {
public:
    int threeSumClosest(vector<int> &nums, int target) {
        int n = nums.size();
        if (n < 3)  return 0;

        std::sort(nums.begin(), nums.end());

        int closestNum = MAX_UNSIGNED_INT;
        int twoClosestNum = 0;
        for (size_t curStart = 0; curStart <= n - 3; )
        {
            twoClosestNum = twoSumClosest(nums, curStart + 1, n - 1, target - nums[curStart]);
            if (std::abs(twoClosestNum + nums[curStart] - target) < std::abs(closestNum - target))
                closestNum = twoClosestNum + nums[curStart];
            curStart = getNext(nums, curStart);
        }

        return closestNum;
    }

private:
    inline int twoSumClosest(const vector<int> &nums, int start, int end, int target)
    {
        int closestSum = MAX_UNSIGNED_INT;
        int totalSum;

        while (start < end)
        {
            totalSum = nums[start] + nums[end];
            if (totalSum == target)
                return target;
            else if (totalSum > target)
            {
                if (totalSum - target < std::abs(closestSum - target))
                    closestSum = totalSum;
                end = getNextReverse(nums, end);
            }
            else
            {
                if (target - totalSum < std::abs(closestSum - target))
                    closestSum = totalSum;
                start = getNext(nums, start);
            }
        }

        return closestSum;
    }

    inline int getNext(const vector<int> &nums, int curPos)
    {
        int n = nums.size();
        curPos++;
        while (curPos < n && nums[curPos] == nums[curPos - 1])
            curPos++;
        return curPos;
    }

    inline int getNextReverse(const vector<int> &nums, int curPos)
    {
        int n = nums.size();
        curPos--;
        while (curPos >= 0 && nums[curPos] == nums[curPos + 1])
            curPos--;
        return curPos;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int S[] = {1, 1, 1, 1};

    vector<int> nums(S, S + sizeof(S) / sizeof(int));
    Solution so;
    int target = 0;

    std::cout << so.threeSumClosest(nums, target) << std::endl;

    return 0;
}

