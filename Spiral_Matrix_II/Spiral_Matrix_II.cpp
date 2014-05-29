// Spiral_Matrix_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        if (n == 0)
        {
            vector<vector<int> >    result;
            return result;
        }

        vector<vector<int> >    resultArr(n);
        vector<int>     lineRes(n);
        for (int i = 0; i < n; i++)
            resultArr[i] = lineRes;

        int startx = 0, starty = 0, len = n, curVal = 1;
        while (len > 0)
        {
            generateBoarderRes(resultArr, startx, starty, len, curVal);
            startx++;
            starty++;
            len -= 2;
        }

        return resultArr;
    }

private:
    inline void generateBoarderRes(vector<vector<int> >&    resultArr, int startx, int starty, int n, int &curVal)
    {
        if (n <= 0) return;

        int i;
        //top row
        for (i = 0; i < n; i++)
            resultArr[startx][starty + i] = curVal++;
        //right col
        for (i = 1; i < n; i++)
            resultArr[startx + i][starty + n - 1] = curVal++;
        //bottom row
        for (i = n - 2; i >= 0; i--)
            resultArr[startx + n - 1][starty + i] = curVal++;
        //left col
        for (i = n - 2; i > 0; i--)
            resultArr[startx + i][starty] = curVal++;        
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

