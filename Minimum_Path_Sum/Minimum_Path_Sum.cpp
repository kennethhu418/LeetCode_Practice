// Minimum_Path_Sum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        int     m = grid.size();    if (m == 0) return 0;
        int     n = grid[0].size(); if (n == 0) return 0;

        char*   buffer = new char[sizeof(int)*m*n + sizeof(int*)*m];
        int**   distArray =  (int**)(buffer + sizeof(int)*m*n);
        for (int i = 0; i < m; i++)
            distArray[i] = (int*)(buffer + sizeof(int)*n*i);

        distArray[m - 1][n - 1] =  grid[m-1][n-1];
        //bottom row
        for (int i = n - 2; i >= 0; i--)
            distArray[m - 1][i] = grid[m-1][i] + distArray[m - 1][i+1];
        //right col
        for (int i = m - 2; i >= 0; i--)
            distArray[i][n - 1] = grid[i][n-1] + distArray[i+1][n - 1];

        int minDist = 0;
        for (int i = m - 2; i >= 0; i--)
        {
            for (int j = n - 2; j >= 0; j--)
                distArray[i][j] = grid[i][j] + (distArray[i][j + 1] < distArray[i + 1][j] ? distArray[i][j + 1] : distArray[i + 1][j]);
        }

        minDist = distArray[0][0];
        delete[] buffer;

        return minDist;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

