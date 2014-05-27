// Set_Matrix_Zeroes.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        int     m = matrix.size();  if (m == 0) return;
        int     n = matrix[0].size();   if (n == 0) return;

        MarkHeaders(matrix);
        SetZeros(matrix);
    }

private:
    void MarkHeaders(vector<vector<int> > &matrix)
    {
        int     m = matrix.size(), n = matrix[0].size(), i, j;

        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (matrix[i][j] == 0)
                {
                    if (matrix[0][j] != 0)
                        matrix[0][j] = 0;
                    if (matrix[i][0] != 0)
                        matrix[i][0] = 0;                        
                }
            }
        }
    }

    void SetZeros(vector<vector<int> > &matrix)
    {
        int     m = matrix.size(), n = matrix[0].size(), i;
        for (i = 1; i < m; i++)
        {
            if (matrix[i][0] == 0)
                InvalidateRow(matrix, i);
        }

        for (i = 0; i < n; i++)
        {
            if (matrix[0][i] == 0)
                InvalidateColumn(matrix, i);
        }        
    }

    inline void InvalidateRow(vector<vector<int> > &matrix, int r)
    {
        for (int i = 0; i < matrix[0].size(); i++)
            matrix[r][i] = 0;
    }

    inline void InvalidateColumn(vector<vector<int> > &matrix, int c)
    {
        for (int i = 0; i < matrix.size(); i++)
            matrix[i][c] = 0;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

