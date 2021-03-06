// Pascal_Triangle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int>> result;
        vector<int> curRow;
        int prevL, prevR;
        if (numRows == 0)
        {
            return result;
        }

        //First row fill first
        curRow.push_back(1);
        result.push_back(curRow);

        for (int i = 1; i < numRows; i++)
        {
            curRow.clear();
            for (int j = 0; j <= i; j++)
            {
                GetPrevVals(result, j, prevL, prevR);
                curRow.push_back(prevL + prevR);
            }
            result.push_back(curRow);
        }

        return result;
    }

private:
    inline void GetPrevVals(const vector<vector<int>> & array, int curIndex, int& prevL, int& prevR)
    {
        int     n = array.size();
        if (curIndex == 0)
            prevL = 0;
        else
            prevL = array[n-1][curIndex-1];

        if (curIndex >= array[n - 1].size())
            prevR = 0;
        else
            prevR = array[n - 1][curIndex];
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

