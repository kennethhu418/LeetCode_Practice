// Two_Sum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> result;
        int n = numbers.size();
        int otherNum;

        if (n < 2)  return result;

        FillMap(numbers);

        for (int i = 0; i < n; i++)
        {
            otherNum = target - numbers[i];
            if (mapA.find(otherNum) == mapA.end())
                continue;

            if (mapA[otherNum] == i)
                continue;

            result.push_back(i + 1);
            result.push_back(mapA[otherNum] + 1);
            break;
        }

        mapA.clear();
        return result;
    }

private:
    unordered_map<int, size_t>  mapA;

    inline void FillMap(vector<int> &numbers)
    {
        int n = numbers.size();
        for (int i = 0; i < n; i++)
            mapA[numbers[i]] = i;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = {10, 23, 8, 3, 34, 8, 9, 23};
    int target = 45;

    vector<int> srcArr(A, A + sizeof(A)/sizeof(int));
    vector<int> result;

    Solution so;
    result = so.twoSum(srcArr, target);

	return 0;
}

