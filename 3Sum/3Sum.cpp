// 3Sum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &nums) {
        int n = nums.size();
        resultArray.clear();
        if (n < 3)  return resultArray;

        std::sort(nums.begin(), nums.end());

        threeSum(nums, 0);
        return resultArray;
    }

private:
    vector<vector<int>> resultArray;
    vector<int> singleComb;
    int     curStartingVal;

    void threeSum(vector<int> &nums, int target) {
        int n = nums.size();

        for (int curStart = 0; curStart <= n - 3; )
        {
            this->curStartingVal = nums[curStart];
            TwoSumInner(nums, curStart + 1, n - 1, target - curStartingVal);
            curStart = getNext(nums, curStart);
        }
    }

    inline void TwoSumInner(const vector<int> &nums, int start, int end, int target)
    {
        int totalSum = 0;

        while (start < end)
        {
            totalSum = nums[start] + nums[end];
            if (totalSum == target)
            {
                singleComb.push_back(curStartingVal);
                singleComb.push_back(nums[start]);
                singleComb.push_back(nums[end]);
                resultArray.push_back(singleComb);
                singleComb.clear();
                start = getNext(nums, start);
                end = getNextReverse(nums, end);
            }
            else if (totalSum > target)
                end = getNextReverse(nums, end);
            else
                start = getNext(nums, start);
        }
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
    int S[] = { -1, 0, 1, 2, -1, -4 };

    vector<int> nums(S, S + sizeof(S) / sizeof(int));
    vector<vector<int>> result;
    Solution so;

    result = so.threeSum(nums);

    int n = result.size(), m;
    for (int i = 0; i < n; i++)
    {
        m = result[i].size();
        for (int j = 0; j < m; j++)
            std::cout << result[i][j] << " ";
        std::cout << std::endl;
    }

    return 0;
}

