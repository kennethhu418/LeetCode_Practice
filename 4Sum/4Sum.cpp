// 4Sum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &nums, int target) {
        int n = nums.size();
        resultArray.clear();

        if (n < 4)  return resultArray;

        std::sort(nums.begin(), nums.end());
        
        int curT;
        for (int outterStart = 0; outterStart <= n - 4; )
        {
            for (int outterEnd = outterStart + 3; outterEnd < n;)
            {
                curT = target - nums[outterStart] - nums[outterEnd];
                curOutterStartVal = nums[outterStart];
                curOutterEndVal = nums[outterEnd];
                TwoSumInner(nums, outterStart + 1, outterEnd - 1, curT);
                outterEnd = getNext(nums, outterEnd);
            }
            outterStart = getNext(nums, outterStart);
        }

        return resultArray;
    }

private:
    vector<vector<int>> resultArray;
    vector<int> singleComb;
    int     curOutterStartVal;
    int     curOutterEndVal;

    inline void TwoSumInner(const vector<int> &nums, int start, int end, int target)
    {
        int totalSum = 0;

        while (start < end)
        {
            totalSum = nums[start] + nums[end];
            if (totalSum == target)
            {
                singleComb.push_back(curOutterStartVal);
                singleComb.push_back(nums[start]);
                singleComb.push_back(nums[end]);
                singleComb.push_back(curOutterEndVal);
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
    int S[] = { -1, 2, 2, -5, 0, -1, 4 };
    int target = 3;

    vector<int> nums(S, S + sizeof(S)/sizeof(int));
    vector<vector<int>> result;
    Solution so;

    result = so.fourSum(nums, target);

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

