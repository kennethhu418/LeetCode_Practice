// Triangle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

/***************************************************************************************************************
Given a triangle, find the minimum path sum from top to bottom.Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
            [2],
          [3, 4],
       [6, 5, 7],
     [4, 1, 8, 3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
**************************************************************************************************************/


/****************************************************Basic Idea****************************************************************************
For row curRow, traverse each element in it and when traverse the curCol's element,
calculate the minimum path length starting from it.
minPathLen[curRow][curCol] = min{ minPathLen[curRow+1][curCol]  + triangle[curRow][curCol] ,  minPathLen[curRow+1][curCol+1]  + triangle[curRow][curCol] }
Thus, we can use the dynamic programming to get the minPathLen[0][0], which is the final result we should return.
Note that at any time, we can just keep the results of two rows: curMinPathLen is curRow's result and prevMinPathLen is curRow+1's results.
When begining to calculate the upper row (curRow-1), curMinPathLen becomes curRow-1's results and prevMinPathLen becomes curRow's results
****************************************************************************************************************************************/

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        if (n == 0) return 0;
        if (n == 1)
        {
            assert(triangle[0].size() == 1);
            return triangle[0][0];
        }

        char* tempBuffer = new char[sizeof(int)*(2*n-1)];
        int *prevMinPathLen = (int*)tempBuffer;
        int *curMinPathLen = (int*)(tempBuffer + sizeof(int)*n);
        int leftPathLen, rightPathLen, *tempPointer;

        //First get last row's minPathLen result
        assert(triangle[n-1].size() == n);
        for (int i = 0; i < n; i++)
            prevMinPathLen[i] = triangle[n-1][i];

        //Now get each row's minPathLen from bottom to top
        for (int curRow = n - 2; curRow >= 0; curRow--)
        {
            assert(triangle[curRow].size() == curRow+1);
            for (int i = 0; i <= curRow; i++)
            {
                leftPathLen = prevMinPathLen[i] + triangle[curRow][i];
                rightPathLen = prevMinPathLen[i+1] + triangle[curRow][i];

                if (leftPathLen < rightPathLen)
                    curMinPathLen[i] = leftPathLen;
                else
                    curMinPathLen[i] = rightPathLen;
            }

            tempPointer = curMinPathLen;
            curMinPathLen = prevMinPathLen;
            prevMinPathLen = tempPointer;
        }

        leftPathLen = prevMinPathLen[0];
        delete[] tempBuffer;
        return leftPathLen;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> row;
    vector<vector<int>> triangle;

    //    [2],
    //    [3, 4],
    //    [6, 5, 7],
    //    [4, 1, 8, 3]
    row.clear();
    row.push_back(2);
    triangle.push_back(row);

    row.clear();
    row.push_back(3);
    row.push_back(4);
    triangle.push_back(row);

    row.clear();
    row.push_back(5);
    row.push_back(6);
    row.push_back(7);
    triangle.push_back(row);

    row.clear();
    row.push_back(4);
    row.push_back(1);
    row.push_back(8);
    row.push_back(3);
    triangle.push_back(row);

    Solution solution;
    printf("%d\n\n", solution.minimumTotal(triangle));

    system("PAUSE");
	return 0;
}

