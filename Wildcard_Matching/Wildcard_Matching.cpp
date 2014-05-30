// Wildcard_Matching.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
using namespace std;

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if (s == NULL && p == NULL)
            return true;

        if (s == NULL || p == NULL)
            return false;

        if (*p == '\0')
        {
            if (*s == '\0') return true;
            else return false;
        }
        else if (*s == '\0')
        {
            if (allStars(p)) return true;
            return false;
        }

        bool    prevPisStar = false;
        while (true)
        {
            if (!foundMatch(s, p, prevPisStar))
                return false;

            if (*p == '*')
            {
                p++;
                prevPisStar = true;
                continue;
            }

            if (*s == '\0' || *p == '\0')
                break;
        }

        return true;
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

    //param prevPisStar: whether *(p-1) == '*'
    inline bool foundMatch(const char* &s, const char* &p, bool prevPisStar)
    {
        const char* curP = p; const char* curS = s; const char* curSStart = s;

        if (*s == '\0')
        {
            if (allStars(p))
                return true;
            return false;
        }

        while (*curSStart != '\0')
        {
            while (*curP != '\0' && *curS != '\0')
            {
                if (*curP == '*')
                    break;

                if (*curP == '?' || *curS == *curP)
                {
                    curS++; curP++; continue;
                }

                if (!prevPisStar)
                    return false;

                curS = ++curSStart;
                curP = p;
            }
            
            if (*curP == '*')   //if p is star, it means the chars before this star in the two strings are the same. We can start a new round of check now
            {
                s = curS; p = curP;
                return true;
            }

            if (*curS == '\0')
            {
                if (allStars(curP))
                {
                    s = curS; p = curP;
                    return true;
                }
                return false;
            }

            if (*curP == '\0')
            {
                if (!prevPisStar)
                    return false;

                //the last char of p string is *, and we reach the end. In this case, if 
                //there is still remaining characters of s string, return true
                if (*(curP - 1) == '*')
                {
                    s = curS; p = curP;
                    return true;
                }
            }

            curS = ++curSStart;
            curP = p;            
        }

        return false;
    }
};

class Solution2 {
public:
    bool isMatch(const char *s, const char *p) {
        const char* star = NULL;
        const char* rs = NULL;

        while (*s) {
            if (*s == *p || *p == '?') { //match
                s++; p++;
                continue;
            }
            if (*p == '*') {
                star = p; // record star
                p++; //match from next p
                rs = s; // record the position of s , star match 0
                continue;
            }
            if (star != NULL) { //if have star in front then backtrace
                p = star + 1; //reset the position of p 
                s = rs + 1;
                rs++; //star match 1,2,3,4,5....
                continue;
            }
            return false; //if not match return false
        }
        while (*p == '*') p++; //skip continue star
        return *p == '\0'; // successful match
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    //string s = "";
    //for (int i = 0; i < 32316; i++)
    //    s += "a";
    //string p = "";
    //p += "*";
    //for (int i = 0; i < 32317; i++)
    //    p += "a";
    //p += "*";
    string s = "b";
    string p = "?*?";

    Solution so;
    printf("%d\n\n", so.isMatch(s.c_str(), p.c_str()));


	return 0;
}

