// Regular_Expression_Matching.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

#define NULL_CHAR '\0'

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if (*p == NULL_CHAR)
            return *s == NULL_CHAR;
        if (*s == NULL_CHAR)
            return allEmpty(p);

        if (*(p + 1) != '*')
        {
            if (*p == *s || *p == '.')
                return isMatch(s + 1, p + 1);
            return false;
        }

        //".*" means we can starting matching from any position of src string
        if (*p == '.')
        {
            while (*s != NULL_CHAR)
            {
                if (isMatch(s, p + 2))
                    return true;
                s++;
            }

            return allEmpty(p);
        }

        //"x*" can mean empty string
        if (isMatch(s, p + 2))
            return true;

        //"x*" (x != '.') can also mean repeat x
        while (*s == *p)
        {
            if (isMatch(s + 1, p + 2))
                return true;
            s++;
        }
        return false;
    }

private:
    inline bool allEmpty(const char* str)
    {
        if (*str == NULL_CHAR)
            return true;

        while (*str != NULL_CHAR)
        {
            if (*(str + 1) != '*')
                return false;
            str += 2;
        }

        return true;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    char    targetString[100];
    char    patternString[100];

    Solution so;

    while (std::cin >> targetString >> patternString)
    {
        std::cout << so.isMatch(targetString, patternString) << std::endl<<std::endl;
    }

	return 0;
}

