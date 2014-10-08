// Permutations.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &nums) {
        vector<vector<int>> resultArr;
        int n = nums.size(); if (n == 0) return resultArr;

        sort(nums.begin(), nums.end());
        while (true){
            resultArr.push_back(nums);
            if (!getNextPermute(nums)) break;
        }
        return resultArr;
    }

private:
    bool getNextPermute(vector<int> &nums){
        int n = nums.size(), decPos = n - 1;
        while (decPos > 0 && nums[decPos - 1] >= nums[decPos]) --decPos;
        if (decPos == 0) return false;

        reverseArray(nums, decPos, n - 1);
        int insertPos = getInsertPos(nums, decPos, n - 1, nums[decPos - 1]);
        swap(nums[decPos - 1], nums[insertPos]);
        return true;
    }

    void reverseArray(vector<int> &nums, int start, int end){
        while (start < end) swap(nums[start++], nums[end--]);
    }

    int getInsertPos(const vector<int> &nums, int start, int end, int target){
        int mid = -1;
        while (start < end){
            mid = ((start + end) >> 1);
            if (nums[mid] <= target) start = mid + 1;
            else end = mid - 1;
        }
        if (start > end || nums[start] > target) return start;
        return start + 1;
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

    Solution   so;
    result = so.permuteUnique(nums);

    for (int i = 0; i < result.size(); i++)
    {
        OutputVector(result[i]);
        cout << endl;
    }
    
	return 0;
}