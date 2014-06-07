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
        resultArray.clear();
        
        int n = nums.size();
        if (n == 0) return resultArray;

        std::sort(nums.begin(), nums.end());
        takeSum(nums, 0, target, 4);
        return resultArray;
    }

private:
    vector<vector<int>> resultArray;
    vector<int> curResult;

    void takeSum(const vector<int>& nums, int curStart, int target, int numCount)
    {
        if (numCount == 0)
        {
            if (target == 0)
                resultArray.push_back(curResult);
            return;
        }

        if (curStart == nums.size())
            return;

        int nextStart = getNextStart(nums, curStart);
        int cnt = std::min(nextStart - curStart, numCount);

        //not include current number
        takeSum(nums, nextStart, target, numCount);

        //include 1 to cnt number of current number
        for (int curCnt = 1; curCnt <= cnt; curCnt++)
        {
            curResult.push_back(nums[curStart]);
            takeSum(nums, nextStart, target - curCnt*nums[curStart], numCount - curCnt);
        }

        for (int curCnt = 1; curCnt <= cnt; curCnt++)
            curResult.pop_back();
    }

    inline int getNextStart(const vector<int>& nums, int curStart)
    {
        int curPos = curStart + 1;
        while (curPos < nums.size() && nums[curPos] == nums[curStart])
            curPos++;
        return curPos;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int S[] = { -497, -494, -484, -477, -453, -453, -444, -442, -428, -420, -401, -393, -392, -381, -357, -357, -327, -323, -306, -285, -284, -263, -262, -254, -243, -234, -208, -170, -166, -162, -158, -136, -133, -130, -119, -114, -101, -100, -86, -66, -65, -6, 1, 3, 4, 11, 69, 77, 78, 107, 108, 108, 121, 123, 136, 137, 151, 153, 155, 166, 170, 175, 179, 211, 230, 251, 255, 266, 288, 306, 308, 310, 314, 321, 322, 331, 333, 334, 347, 349, 356, 357, 360, 361, 361, 367, 375, 378, 387, 387, 408, 414, 421, 435, 439, 440, 441, 470, 492 };
    int target = 1682;

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

