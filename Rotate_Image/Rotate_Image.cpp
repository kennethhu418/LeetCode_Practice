// Rotate_Image.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();

        if (n < 2)
            return;

        assert(matrix[0].size() == n);

        int size = n, x = 0, y = 0;
        while (size > 1)
        {
            RotateBorder(matrix, x, y, size);
            x++;
            y++;
            size -= 2;
        }
        
        return;
    }

private:
    void RotateBorder(vector<vector<int> > &matrix, int x, int y, int n)
    {
        int orgTopRight =0;
        int times = n - 1;

        while (times > 0)
        {
            orgTopRight = matrix[x][y];

            //left column
            for (int i = 0; i <= n - 2; i++)
                matrix[x + i][y] = matrix[x + i + 1][y];
            //bottom row
            for (int i = 0; i <= n - 2; i++)
                matrix[x + n - 1][y + i] = matrix[x + n - 1][y + i + 1];
            //right column
            for (int i = n - 2; i >= 0; i--)
                matrix[x + i + 1][y + n - 1] = matrix[x + i][y + n - 1];
            //top row
            for (int i = n - 1; i > 1; i--)
                matrix[x][y + i] = matrix[x][y + i - 1];

            matrix[x][y+1] = orgTopRight;
            times--;
        }
    }
};

class Solution2 {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();

        if (n < 2)
            return;

        assert(matrix[0].size() == n);

        FlipMatrixHorizon(matrix);
        FlipMatrixDiagnal(matrix);

        return;
    }

private:
    inline void FlipMatrixHorizon(vector<vector<int> > &matrix)
    {
        int n = matrix.size();
        int endRow = n / 2;
        int temp;

        for (int row = 0; row < endRow; row++)
        {
            for (int i = 0; i < n; i++)
            {
                temp = matrix[row][i];
                matrix[row][i] = matrix[n - row - 1][i];
                matrix[n - row - 1][i] = temp;                
            }
        }
    }

    inline void FlipMatrixDiagnal(vector<vector<int> > &matrix)
    {
        int n = matrix.size();
        int curStart = -1;
        int temp;

        for (int row = 0; row < n; row++)
        {
            curStart++;
            for (int col = curStart + 1; col < n; col++)
            {
                temp = matrix[row][col];
                matrix[row][col] = matrix[col][row];
                matrix[col][row] = temp;
            }
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> singleLine;
    vector<vector<int>> matrix;
    singleLine.push_back(1);
    singleLine.push_back(2);
    singleLine.push_back(3);
    singleLine.push_back(4);
    matrix.push_back(singleLine);
    singleLine.clear();
    singleLine.push_back(5);
    singleLine.push_back(6);
    singleLine.push_back(7);
    singleLine.push_back(8);
    matrix.push_back(singleLine); 
    singleLine.clear();
    singleLine.push_back(9);
    singleLine.push_back(10);
    singleLine.push_back(11);
    singleLine.push_back(12);
    matrix.push_back(singleLine);
    singleLine.clear();
    singleLine.push_back(13);
    singleLine.push_back(14);
    singleLine.push_back(15);
    singleLine.push_back(16);
    matrix.push_back(singleLine);
    singleLine.clear();
 

    Solution    so;
    so.rotate(matrix);

	return 0;
}

