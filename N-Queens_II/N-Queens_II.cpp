// N-Queens_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class Solution {
public:
    int totalNQueens(int n) {
        if (n < 2)
            return n;

        bool* colAcc = new bool[n];
        int*  colInEachRow = new int[n];
        int   totalN = 0;
        memset(colAcc, 0, sizeof(bool)*n);

        solveNQueens(totalN, n, n, colAcc, colInEachRow);
        delete[] colAcc;    delete[] colInEachRow;
        return totalN;
    }

private:
    void solveNQueens(int& totalN, int leftQ, int n, bool* colAcc, int* colInEachRow)
    {
        if (leftQ == 0)
        {
            totalN++;
            return;
        }

        bool fit = false;

        for (int j = 0; j < n; j++)
        {
            if (colAcc[j])  continue;

            fit = true;
            for (int i = 0; i < n - leftQ; i++)
            {
                if (abs(n - leftQ - i) == abs(j - colInEachRow[i]))
                {
                    fit = false;
                    break;
                }
            }

            if (!fit)
                continue;

            colAcc[j] = true;
            colInEachRow[n - leftQ] = j;
            solveNQueens(totalN, leftQ - 1, n, colAcc, colInEachRow);
            colAcc[j] = false;
        }

    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Solution    s;
    s.totalNQueens(1);
	return 0;
}

