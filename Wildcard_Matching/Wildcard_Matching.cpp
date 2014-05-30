// Wildcard_Matching.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if (s == NULL && p == NULL)
            return true;

        if (s == NULL || p == NULL)
            return false;

        while (*s != '\0' && *p != '\0')
        {
            if (!foundMatch(s, p))
                return false;

            if (*s == '\0' || *p == '\0')
                break;

            p++;
        }

        if (*s == '\0' && *p == '\0')
            return true;

        if (*s == '\0' && allStars(p))
            return true;

        return false;
    }
    
private:
    inline bool allStars(const char* p)
    {
        if (*p == '\0')
            return true;
        while (*p != '\0')
        {
            if (*p != '*')
                return false;
            p++;
        }
        return true;
    }

    inline bool foundMatch(const char* &s, const char* &p)
    {
        const char* curP = p; const char* curS = s; const char* curSStart = s;
        while (*curP != '\0' && *curS != '\0')
        {
            if (*curP == '*')
                break;

            if (*curP == '?' || *curS == *curP)
            {
                curS++; curP++; continue;
            }

            curS = ++curSStart;
            curP = p;                
        }

        s = curS; p = curP;

        if (*curP == '*')
             return true;

        //here *curS == '\0' || *curP == '\0', which does not certainly mean that
        //the two strings are matched. But we still return true for the caller to
        //process *curS == '\0' || *curP == '\0' case.
        return true;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    const char* s = "abcdeabckmabc";
    const char* p = "a*km**??ec**";

    Solution so;
    printf("%d\n\n", so.isMatch(s, p));


	return 0;
}

