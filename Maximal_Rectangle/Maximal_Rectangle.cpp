// Maximal_Rectangle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

typedef struct __ResPoint
{
    int width;
    int height;
    int width_line_length;
    int height_line_length;
    __ResPoint(int w = 0, int h = 0, int wl = 0, int hl = 0){ width = w; height = h; width_line_length = wl; height_line_length = hl; }
}ResPoint;

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        int m = matrix.size();
        if (m == 0)
            return 0;

        int n = matrix[0].size();
        if (n == 0)
            return 0;

        ResPoint**  resArr = new ResPoint*[m];
        ResPoint zeroResult = {0,0,0,0};
        ResPoint    right, down;
        for (int i = 0; i < m; i++)
            resArr[i] = new ResPoint[n];

        int     maxRegion = 0;
        resArr[m - 1][n - 1] = (matrix[m - 1][n - 1] == '0' ? zeroResult : ResPoint(1, 1, 1, 1));
        if (resArr[m - 1][n - 1].width > maxRegion)
            maxRegion = resArr[m - 1][n - 1].width;

        for (int i = m - 2; i >= 0; i--)
        {
            if (matrix[i][n - 1] == '0')
                resArr[i][n - 1] = zeroResult;
            else
                resArr[i][n - 1] = ResPoint(1, 1 + resArr[i + 1][n - 1].height, 1, 1 + resArr[i + 1][n - 1].height);

            if (resArr[i][n - 1].height > maxRegion)
                maxRegion = resArr[i][n - 1].height;
        }

        for (int i = n - 2; i >= 0; i--)
        {
            if (matrix[m - 1][i] == '0')
                resArr[m - 1][i] = zeroResult;
            else
                resArr[m - 1][i] = ResPoint(1 + resArr[m - 1][i + 1].width, 1, 1 + resArr[m - 1][i + 1].width, 1);
            
            if (resArr[m-1][i].width > maxRegion)
                maxRegion = resArr[m - 1][i].width;
        }

        for (int i = m - 2, j = n - 2; i >= 0 && j >= 0; i--, j--)
        {
            for (int k = j; k >= 0; k--)
            {
                if (matrix[i][k] == '0')
                {
                    resArr[i][k] = zeroResult;
                    continue;
                }

                right = resArr[i][k + 1];
                down = resArr[i+1][k];

                int curMax = 0;
                resArr[i][k].width_line_length = 1 + right.width_line_length;
                resArr[i][k].height_line_length = 1 + down.height_line_length;
                curMax = getMax(resArr[i][k].width_line_length, resArr[i][k].height_line_length);

                int rightDownRectWidth = getMin(right.width, down.width - 1);
                int rightDownRectHeight = getMin(right.height - 1, down.height);
                if (rightDownRectWidth > 0 && rightDownRectHeight > 0)
                {
                    resArr[i][k].width = rightDownRectWidth + 1;
                    resArr[i][k].height = rightDownRectHeight + 1;
                    if (resArr[i][k].width*resArr[i][k].height > curMax)
                        curMax = resArr[i][k].width*resArr[i][k].height;
                }

                if (curMax > maxRegion)
                    maxRegion = curMax;
            }

            for (int k = i-1; k >= 0; k--)
            {
                if (matrix[k][j] == '0')
                {
                    resArr[k][j] = zeroResult;
                    continue;
                }

                right = resArr[k][j+1];
                down = resArr[k+1][j];

                int curMax = 0;
                resArr[k][j].width_line_length = 1 + right.width_line_length;
                resArr[k][j].height_line_length = 1 + down.height_line_length;
                curMax = getMax(resArr[k][j].width_line_length, resArr[k][j].height_line_length);

                int rightDownRectWidth = getMin(right.width, down.width - 1);
                int rightDownRectHeight = getMin(right.height - 1, down.height);
                if (rightDownRectWidth > 0 && rightDownRectHeight > 0)
                {
                    resArr[k][j].width = rightDownRectWidth + 1;
                    resArr[k][j].height = rightDownRectHeight + 1;
                    if (resArr[k][j].width*resArr[k][j].height > curMax)
                        curMax = resArr[k][j].width*resArr[k][j].height;
                }

                if (curMax > maxRegion)
                    maxRegion = curMax;
            }
        }

        for (int i = 0; i < m; i++)
            delete[] resArr[i];
        delete[] resArr;

        return maxRegion;
    }

private:
    inline int getMax(int a, int b)
    {
        return a > b ? a : b;
    }

    inline int getMin(int a, int b)
    {
        return a < b ? a : b;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<char> v;
    v.push_back('1');
    v.push_back('1');
    v.push_back('1');
    v.push_back('1');

    vector<vector<char>> vv;
    vv.push_back(v);
    vv.push_back(v);
    vv.push_back(v);

    Solution so;
    cout<<so.maximalRectangle(vv)<<endl<<endl;

    system("PAUSE");
	return 0;
}

