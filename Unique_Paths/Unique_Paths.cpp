// Unique_Paths.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0)   return 0;
        if (m == 1 || n == 1)   return 1;

        char*   buffer = new char[sizeof(int)*2*n];
        int *curRow = (int*)buffer;
        int *prevRow = (int*)(buffer + sizeof(int)* n);
        int* tmpRow = NULL;

        //last row
        for (int i = n - 1; i >= 0; i--)
            prevRow[i] = 1;

        //traverse each above row
        for (int i = m - 2; i >= 0; i--)
        {
            curRow[n - 1] = 1;
            for (int j = n - 2; j >= 0; j--)
                curRow[j] = curRow[j + 1] + prevRow[j];

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

