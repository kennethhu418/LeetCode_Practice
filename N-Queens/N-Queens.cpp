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

        bool* rowAcc = new bool[2*n];
        bool* colAcc = rowAcc + n;
        memset(rowAcc, 0, sizeof(bool)*2*n);

        solveNQueens(resultA, singleResult, n, n, rowAcc, colAcc);
        delete[] rowAcc;
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
        int leftQ, int n, bool* rowAcc, bool* colAcc)
    {
        if (leftQ == 0)
        {
            result.push_back(singleResult);
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (rowAcc[i])  continue;
            rowAcc[i] = true;
            for (int j = 0; j < n; j++)
            {
                if (colAcc[j])  continue;
                colAcc[j] = true;
                singleResult[i][j] = 'Q';
                solveNQueens(result, singleResult, leftQ - 1, n, rowAcc, colAcc);
                singleResult[i][j] = '.';
                colAcc[j] = false;
            }
            rowAcc[i] = false;
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    Solution s;
    s.solveNQueens(2);
	return 0;
}

