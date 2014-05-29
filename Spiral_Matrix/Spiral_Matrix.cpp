// Spiral_Matrix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        vector<int>     result;

        int m = matrix.size();  if (m == 0) return  result;
        int n = matrix[0].size(); if (n == 0)   return result;

        int x = 0, y = 0, w = n, h = m, i = 0;
        while (w > 0 && h > 0)
        {
            //top row
            for (i = 0; i < w; i++)
                result.push_back(matrix[x][y + i]);

            //right col
            for (i = 1; i < h; i++)
                result.push_back(matrix[x + i][y + w - 1]);

            if (h > 1)
            {
                //bottom row
                for (i = w - 2; i >= 0; i--)
                    result.push_back(matrix[x + h - 1][y + i]);
            }

            if (w > 1)
            {
                //left col
                for (i = h - 2; i > 0; i--)
                    result.push_back(matrix[x + i][y]);
            }

            x++;    y++;    w -= 2; h -= 2;
        }

        return result;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> singleLine;
    singleLine.push_back(2);
    singleLine.push_back(3);
    vector<vector<int>> matrix;
    matrix.push_back(singleLine);

    Solution    so;
    so.spiralOrder(matrix);

	return 0;
}