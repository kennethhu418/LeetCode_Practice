// Permutations.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        int n = num.size();
        vector<vector<int>> result;
        if (n == 0) return result;
        if (n == 1)
        {
            result.push_back(num);
            return result;
        }

        sort(num.begin(), num.end());
        alreadyInResult = new bool[n];
        memset(alreadyInResult, 0, sizeof(bool)*n);

        permuteUnique(result, num, 0);

        delete[] alreadyInResult;
        return result;
    }

private:
    bool*       alreadyInResult;
    vector<int> singlePermutationResult;

    void permuteUnique(vector<vector<int>> &result, vector<int> &num, int curPos)
    {
        int n = num.size();

        if (curPos == n)
        {
            result.push_back(singlePermutationResult);
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (!alreadyInResult[i])
            {
                alreadyInResult[i] = true;
                singlePermutationResult.push_back(num[i]);
                permuteUnique(result, num, curPos + 1);
                singlePermutationResult.pop_back();
                alreadyInResult[i] = false;

                while (i + 1 < n && num[i + 1] == num[i])
                    i++;
            }
        }
    }
};

class Solution2 {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        int n = num.size();
        vector<vector<int>> result;
        if (n == 0) return result;
        if (n == 1)
        {
            result.push_back(num);
            return result;
        }

        permuteUnique(result, num, 0);

        return result;
    }

private:
    void permuteUnique(vector<vector<int>> &result, vector<int> &num, int curPos)
    {
        int n = num.size();

        if (curPos == n)
        {
            result.push_back(num);
            return;
        }

        unordered_set<int>  hashA;

        for (int i = curPos; i < n; i++)
        {
            if (hashA.find(num[i]) != hashA.end())
                continue;

            hashA.insert(num[i]);
            swap(num[curPos], num[i]);
            permuteUnique(result, num, curPos + 1);
            swap(num[curPos], num[i]);
        }
    }
};

void OutputVector(const vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
}

int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> nums;
    vector<vector<int>> result;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(1);

    Solution2    so;
    result = so.permuteUnique(nums);

    for (int i = 0; i < result.size(); i++)
    {
        OutputVector(result[i]);
        cout << endl;
    }
    
	return 0;
}