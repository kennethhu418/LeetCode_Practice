// Search_a_2D_Matrix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int     m = matrix.size();    if (m == 0)   return false;
        int     n = matrix[0].size();   if (n == 0) return false;

        if (target < matrix[0][0] || target > matrix[m - 1][n - 1])
            return false;

        int     targetLine = findTargetLine(matrix, target);
        assert(targetLine >= 0 && targetLine < m);

        return  findElement(matrix[targetLine], target);
    }

private:
    inline  int findTargetLine(vector<vector<int> > &matrix, int target)
    {
        int start = 0, end = matrix.size() - 1, mid = 0;

        while (start < end)
        {
            mid = (start + end) / 2;
            if (target == matrix[mid][0])
                return mid;

            if (target < matrix[mid][0])
            {
                end = mid - 1;
                continue;
            }

            start = mid;
        }

        assert(target >= matrix[start][0] && (start == matrix.size() - 1 || matrix[start+1][0] > target));
        return start;
    }

    inline bool findElement(vector<int> &arr, int target)
    {
        int     start = 0, end = arr.size() - 1, mid;
        while (start < end)
        {
            mid = (start+end)/2;
            if (arr[mid] == target)
                return true;
            if (arr[mid] > target)
                end = mid - 1;
            else
                start = mid + 1;
        }

        return (target == arr[start]);
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<int>     singleLine;
    vector<vector<int>> matrix;

    singleLine.push_back(1);
    matrix.push_back(singleLine);
    singleLine.clear();
    singleLine.push_back(3);
    matrix.push_back(singleLine);
    singleLine.clear();

    Solution    so;
    so.searchMatrix(matrix, 2);

	return 0;
}

