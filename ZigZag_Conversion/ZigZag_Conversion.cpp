// ZigZag_Conversion.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>

using std::string;

class Solution {
public:
    string convert(string s, int nRows) {
        int sCount = s.size();
        if (sCount < 2 || nRows < 2)
            return s;

        string result(sCount, ' ');

        ConstructRowStartArray(sCount, nRows);

        int curRow = 0, curPos = 0;
        while (curPos < sCount)
        {
            for (curRow = 0; curRow < nRows && curPos < sCount; curRow++)
            {
                result[rowStartIndex[curRow]] = s[curPos];
                rowStartIndex[curRow]++;
                curPos++;                
            }

            for (curRow = nRows - 2; curRow > 0 && curPos < sCount; curRow--)
            {
                result[rowStartIndex[curRow]] = s[curPos];
                rowStartIndex[curRow]++;
                curPos++;
            }
        }

        return result;
    }

private:
    std::vector<int> rowStartIndex;

    void ConstructRowStartArray(int sCount, int rowCount)
    {
        if (rowCount == 0 || sCount == 0)  return;

        rowStartIndex.resize(rowCount);
        if (rowCount == 1)
        {
            rowStartIndex[0] = 0;
            return;
        }

        int unitSize = 2 * (rowCount - 1);
        int unitCount = sCount / unitSize;
        int remainingCount = sCount - unitCount*unitSize;
        int totalCount = 0;

        rowStartIndex[0] = unitCount;
        rowStartIndex[rowCount - 1] = unitCount;
        for (int i = 1; i < rowCount - 1; i++)
            rowStartIndex[i] = 2 * unitCount;

        for (int i = 0; i < rowCount && remainingCount; i++)
        {
            rowStartIndex[i]++;
            remainingCount--;
        }

        for (int i = rowCount - 2; i > 0 && remainingCount; i--)
        {
            rowStartIndex[i]++;
            remainingCount--;
        }

        for (int i = 0; i < rowCount; i++)
        {
            remainingCount = rowStartIndex[i];
            rowStartIndex[i] = totalCount;
            totalCount += remainingCount;
        }

        assert(totalCount == sCount);
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;

    string s = "PAYPALISHIRING";
    int rows = 3;
    Solution so;

    while (cin >> s)
    {
        cin >> rows;

        cout << so.convert(s, rows) << endl;
        cout << "----------------------------------" << endl;
    }


	return 0;
}

