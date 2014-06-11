// Regular_Expression_Matching.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if (s == NULL || p == NULL)
            return false;

        if (*s == '\0' && *p == '\0')
            return true;

        if (*p == '\0')
            return false;

        bool hasLeadingStars = (*p == '*');
        if (hasLeadingStars)
        {
            p = skipStars(p);
            if (*p == '\0')
                return true;
        }

        if (*s == '\0')
            return false;

        const char* s_start = s, *p_start = p, *p_end = NULL;
        const char* firstMatchS = NULL;
        p_end = getNextStar(p_start);

        while (*s_start != '\0')
        {
            if (s_start == s && !hasLeadingStars)
                firstMatchS = findLastMatch(s_start, p_start, p_end, true);
            else
                firstMatchS = findLastMatch(s_start, p_start, p_end);
            if (firstMatchS == NULL)
                return false;

            s_start = firstMatchS + (p_end - p_start);
            if (*p_end == '\0')
            {
                if (*s_start == '\0')
                    return true;
                return false;
            }

            p_start = skipStars(p_end);
            if (*p_start == '\0')
                return true;
            p_end = getNextStar(p_start);
        }

        return false;
    }

private:
    inline const char* skipStars(const char* s)
    {
        while (*s == '*')
            s++;
        return s;
    }

    inline const char* getNextStar(const char* s)
    {
        while (*s != '\0')
        {
            if (*s == '*')
                return s;
            s++;
        }

        return s;
    }

    inline const char* findLastMatch(const char* s, const char* p_start, const char* p_end, bool alignedMatch = false)
    {
        const char* curSStart = s, *curS = s, *curP = p_start;
        const char* resultS = NULL;

        while (*curSStart != '\0')
        {
            curP = p_start;
            curS = curSStart;
            while (*curS != '\0' && curP < p_end)
            {
                if (*curS != *curP && *curP != '.')
                    break;
                curS++; curP++;
            }

            if (*curS == '\0' && curP == p_end)
            {
                resultS = curSStart;
                break;
            }

            if (*curS == '\0')
                break;

            if (curP == p_end)
            {
                if (alignedMatch)
                    return curSStart;

                resultS = curSStart;
                curSStart++;
                continue;
            }

            if (alignedMatch)
                return NULL;

            curSStart++;
        }

        return resultS;
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

