// ZigZag_Conversion.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

/************************************************************************************************************************
Version 2: With O(n) time complexity and O(1) space time complexity
充分利用每个zigzag是2*nRows - 2个字符就可以。对于每一行先把往下走的那一列的字符加进去，然后有往上走的字符再加进去即可
 ************************************************************************************************************************/
class Solution {
public:
    string convert(const string &s, int nRows) {
        int n = s.size();
        if (n == 1 || nRows == 1) return s;

        string result;
        int unitSize = 2 * nRows - 2, increaseLen = 0;

        for (int curRow = 0; curRow < nRows; ++curRow){
            increaseLen = ((nRows - 1 - curRow) << 1);
            for (int i = curRow; i < n; i += unitSize){
                result += s[i];
                if (curRow > 0 && curRow < nRows - 1 && i + increaseLen < n)
                    result += s[i + increaseLen];
            }
        }

        return result;
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

