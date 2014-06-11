// Integer_to_Roman.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <assert.h>

using std::string;

class Solution {
public:
    string intToRoman(int num) {
        result.clear();
        if (num == 0)
            return result;

        int curPosNum = num / 1000;
        num = num - 1000 * curPosNum;
        if (curPosNum > 3)
            assert(0);
        else
            appendChar('M', curPosNum);

        curPosNum = num / 100;
        num = num - 100 * curPosNum;
        if (curPosNum == 9)
            result += "CM";
        else if (curPosNum == 4)
            result += "CD";
        else if (curPosNum < 4)
            appendChar('C', curPosNum);
        else
        {
            result += 'D';
            appendChar('C', curPosNum - 5);
        }

        curPosNum = num / 10;
        num = num - 10 * curPosNum;
        if (curPosNum == 9)
            result += "XC";
        else if (curPosNum == 4)
            result += "XL";
        else if (curPosNum < 4)
            appendChar('X', curPosNum);
        else
        {
            result += 'L';
            appendChar('X', curPosNum - 5);
        }

        curPosNum = num;
        if (curPosNum == 9)
            result += "IX";
        else if (curPosNum == 4)
            result += "IV";
        else if (curPosNum < 4)
            appendChar('I', curPosNum);
        else
        {
            result += 'V';
            appendChar('I', curPosNum - 5);
        }

        return result;
    }

private:
    string result;

    inline void appendChar(const char a, int n)
    {
        for (int i = 0; i < n; i++)
            result += a;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int integer;
    string result;
    Solution so;

    while (std::cin >> integer)
    {
        std::cout << so.intToRoman(integer) << std::endl << std::endl;
    }

	return 0;
}

