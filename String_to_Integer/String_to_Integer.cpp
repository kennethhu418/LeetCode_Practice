// String_to_Integer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

#define SIGN_POSITIVE   -1
#define SIGN_NEGATIVE -2
#define INVALID_CHAR    -3
#define MAX_INT 0x7FFFFFFF
#define MIN_INT  0x80000000

class Solution {
public:
    int atoi(const char *str) {
        if (str == NULL)    return 0;
        
        str = skipSpaces(str);
        if (*str == '\0')
            return 0;

        int curNum = getValidNumber(*str);
        if (curNum == INVALID_CHAR)
            return 0;

        bool isNegative = false;
        unsigned int result = 0, maxVal = MAX_INT;

        if (curNum == SIGN_POSITIVE)
            str++;
        else if (curNum == SIGN_NEGATIVE)
        {
            isNegative = true;
            maxVal++;
            str++;
        }

        while (*str != '\0')
        {
            curNum = getValidNumber(*str);
            if (curNum < 0)
                break;

            if (result > maxVal / 10)
                return isNegative ? MIN_INT : MAX_INT;

            result *= 10;

            if (maxVal - curNum < result)
                return isNegative ? MIN_INT : MAX_INT;

            result += curNum;
            str++;
        }

        if (!isNegative)
            return result;

        if (result == maxVal)
            return MIN_INT;
        return 0 - (int)result;
    }

private:
    inline const char* skipSpaces(const char* str)
    {
        while (*str == ' ' || *str == '\t')
            str++;
        return str;
    }

    inline int getValidNumber(char a)
    {
        if (a >= '0' && a <= '9')
            return a - '0';

        if (a == '+')
            return SIGN_POSITIVE;
        else if (a == '-')
            return SIGN_NEGATIVE;

        return INVALID_CHAR;        
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;

    char str[30];
    Solution so;

    while (cin >> str)
    {
        cout << so.atoi(str) << endl;
    }    

	return 0;
}

