// Combination_Sum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        int n = candidates.size();
        vector<vector<int> > result;
        if (n == 0 || target <= 0)
            return result;

        std::sort(candidates.begin(), candidates.end());

        if (combinationSum(candidates, 0, result, target))
            return result;

        result.clear();
        return result;
    }

private:
    bool combinationSum(const vector<int> &candidates, int start, vector<vector<int> > &result, int target)
    {
        if (target == 0)
            return true;

        int n = candidates.size();

        if (start == n || target < candidates[start])
            return false;

        int nextStart = getNextDifferentNum(candidates, start);
        vector<vector<int> > subResult;
        for (int i = 0;; i++)
        {
            if (i*candidates[start] > target)
                break;

            if (combinationSum(candidates, nextStart, subResult, target - i*candidates[start]))
                combineResult(result, candidates[start], i, subResult);
            subResult.clear();
        }

        if (!result.empty())
            return true;
        return false;
    }

    inline int getNextDifferentNum(const vector<int> &candidates, int start)
    {
        int n = candidates.size();
        int org = candidates[start];
        start++;
        while (start < n && candidates[start] == org)
            start++;
        return start;
    }

    inline void combineResult(vector<vector<int> > &result, int preNum, int repCount, const vector<vector<int> > &subResult)
    {
        int n = subResult.size(), m = 0;
        vector<int> singleComb;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < repCount; j++)
                singleComb.push_back(preNum);

            m = subResult[i].size();
            for (int j = 0; j < m; j++)
                singleComb.push_back(subResult[i][j]);

            result.push_back(singleComb);
            singleComb.clear();
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> candidates;
    //candidates.push_back(2);
    candidates.push_back(7);
    //candidates.push_back(2);
    //candidates.push_back(6);
    //candidates.push_back(3);

    Solution so;
    vector<vector<int> > result = so.combinationSum(candidates, 7);

	return 0;
}

