// Letter_Combinations_of_a_Phone_Number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>

using std::string;
using std::vector;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        this->size = digits.size();
        this->digits = digits;

        resultArray.clear();
        curResult.clear();

        letterCombination(0);

        return resultArray;
    }

private:
    vector<string>  resultArray;
    string  curResult;
    string  digits;
    int     size;

    void letterCombination(int curPos)
    {
        if (curPos == size)
        {
            resultArray.push_back(curResult);
            return;
        }

        curResult += ' ';
        int cnt = 0;
        char startChar = getChar(digits[curPos], cnt);
        for (size_t i = 0; i < cnt; i++)
        {
            curResult[curResult.size() - 1] = startChar + i;
            letterCombination(curPos + 1);
        }

        curResult.pop_back();
    }

    inline char getChar(char num, int& count)
    {
        if (num == '0')
        {
            count = 1; return ' ';
        }

        if (num < '2' || num > '9')
        {
            assert(0);
        }

        if (num < '7')
        {
            count = 3;
            return ('a' + 3*(num - '2'));
        }

        if (num == '7' || num == '9')
        {
            count = 4;
            return (num == '7' ? 'p' : 'w');
        }

        //num == '8'
        count = 3;
        return 't';
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    string strnums;

    Solution so;
    vector<string> result;
    vector<string>::const_iterator iter;
    while (std::cin >> strnums)
    {
        result = so.letterCombinations(strnums);
        for (iter = result.begin(); iter != result.end(); iter++)
            std::cout << *iter << " ";
        std::cout << std::endl << std::endl;
    }

	return 0;
}

