// Unique_Paths_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        int     m = obstacleGrid.size();    if (m == 0) return 0;
        int     n = obstacleGrid[0].size();      if (n == 0) return 0;

        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
            return 0;

        char*   buffer = new char[sizeof(int)* 2 * n];
        int *curRow = (int*)buffer;
        int *prevRow = (int*)(buffer + sizeof(int)* n);
        int* tmpRow = NULL;

        //last row
        prevRow[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--)
        {
            if (obstacleGrid[m - 1][i] == 1)
                prevRow[i] = 0;
            else
                prevRow[i] = prevRow[i+1];
        }

        //traverse each top row
        for (int i = m - 2; i >= 0; i--)
        {
            curRow[n - 1] = obstacleGrid[i][n - 1] == 1 ? 0 : prevRow[n - 1];

            for (int j = n - 2; j >= 0; j--)
            {
                if (obstacleGrid[i][j] == 1)
                    curRow[j] = 0;
                else
                    curRow[j] = curRow[j + 1] + prevRow[j];
            }

            tmpRow = curRow;
            curRow = prevRow;
            prevRow = tmpRow;
        }

        int result = prevRow[0];
        delete[] buffer;
        return result;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

