// Pascal_Triangle_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> prevRow;
        vector<int> curRow;
        vector<int> *prevR = &prevRow;
        vector<int> *curR = &curRow;
        vector<int> *tempR;
        int prevLV, prevRV;

        //First fill first row
        prevR->push_back(1);

        for (int i = 1; i <= rowIndex; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                GetPrevVals(*prevR, j, prevLV, prevRV);
                curR->push_back(prevLV + prevRV);
            }

            tempR = curR;
            curR = prevR;
            prevR = tempR;
            curR->clear();            
        }

        return *prevR;
    }

private:
    inline void GetPrevVals(const vector<int> & array, int curIndex, int& prevL, int& prevR)
    {
        if (curIndex == 0)
            prevL = 0;
        else
            prevL = array[curIndex - 1];

        if (curIndex >= array.size())
            prevR = 0;
        else
            prevR = array[curIndex];
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

