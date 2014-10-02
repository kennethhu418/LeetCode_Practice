// ZigZag_Conversion.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

/************************************************************************************************************************
Version 2: With O(n) time complexity and O(1) space time complexity
�������ÿ��zigzag��2*nRows - 2���ַ��Ϳ��ԡ�����ÿһ���Ȱ������ߵ���һ�е��ַ��ӽ�ȥ��Ȼ���������ߵ��ַ��ټӽ�ȥ����
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

