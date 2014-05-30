// N-Queens.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string>>  resultA;
        if (n == 0)
            return resultA;

        vector<string>  singleResult;
        InitializeSingleResult(singleResult, n);

        bool* colAcc = new bool[n];
        int*  colInEachRow = new int[n];
        memset(colAcc, 0, sizeof(bool)*n);

        solveNQueens(resultA, singleResult, n, n, colAcc, colInEachRow);
        delete[] colAcc;    delete[] colInEachRow;
        return resultA;
    }

private:
    void InitializeSingleResult(vector<string> &singleResult, int n)
    {
        string s = "";
        for (int i = 0; i < n; i++)
            s += ".";
        for (int i = 0; i < n; i++)
            singleResult.push_back(s);
    }

    void solveNQueens(vector<vector<string>> &result, vector<string> &singleResult, 
        int leftQ, int n, bool* colAcc, int* colInEachRow)
    {
        if (leftQ == 0)
        {
            result.push_back(singleResult);
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
            singleResult[n - leftQ][j] = 'Q';
            solveNQueens(result, singleResult, leftQ - 1, n, colAcc, colInEachRow);
            singleResult[n - leftQ][j] = '.';
            colAcc[j] = false;
        }

    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    Solution s;
    s.solveNQueens(1);
	return 0;
}

