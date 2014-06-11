// Regular_Expression_Matching.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

//题意理解错了有木有！！！
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        const char* curS = s, *curP = p;

        while (*curS != '\0' && *curP != '\0' && *(curP+1) != '*')
        {
            if (*curS != *curP && *curP != '.')
                break;
            curS++; curP++;
        }

        if (*curS == '\0' && *curP == '\0')
            return true;

        if (*curS == '\0')
        {
            if (isEmpty(curP))  return true;
            return false;
        }

        if (*curP == '\0')  return false;

        //Now neither curS nor curP is '\0'. So it must be either curS != curP or curP + 1 == '*'

        //If it is the case that curS != curP, rather than curP + 1 == '*', return false
        if (*curS != *curP && *(curP + 1) != '*')
            return false;

        //It is the case that curP + 1 == '*'

        if (*curP == '.')
        {
            while (*curS != '\0')
            {
                if (isMatch(curS, curP + 2))
                    return true;
                curS++;
            }

            return false;
        }
        
        //ignore the curP char
        if (isMatch(curS, curP + 2))
            return true;

        while (*curS != '\0' && *curS == *curP)
        {
            if (isMatch(curS + 1, curP + 2))
                return true;
            curS++;
        }

        return false; 
    }

private:
    inline bool isEmpty(const char* s)
    {
        if (*s == '\0')
            return true;

        while (*s != '\0')
        {
            if (*s != '*')
            {
                if (*(s + 1) == '\0' || *(s + 1) != '*')
                    return false;
            }
            s++;
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

