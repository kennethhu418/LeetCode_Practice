// Valid_Number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    bool isNumber(const char *s) {
        if (s == NULL)
            return false;

        int start = -1, end = -1;
        if (!getStringStartEnd(s, start, end))
            return false;

        bool hasDot = false;
        bool hasE = false;

        for (int i = start; i <= end; i++)
        {
            if (s[i] == ' ')
                return false;

            if (s[i] == '-')
            {
                if (i == end)
                    return false;

                if (!isNumber(s[i + 1]))
                    return false;

                if (i == start)
                    continue;          
                else if (s[i - 1] == 'e' || s[i - 1] == 'E')
                    continue;
                return false;
            }

            if (s[i] == '.')
            {
                if (hasDot || hasE)
                    return false;

                if (i != end && !isNumber(s[i + 1]))
                    return false;

                if (i != start && !isNumber(s[i - 1]))
                    return false;

                hasDot = true;
                continue;
            }

            if (s[i] == 'e' || s[i] == 'E')
            {
                if (i == start || i == end || hasE)
                    return false;

                hasE = true;
                continue;
            }

            if (!isNumber(s[i]))
                return false;
        }

        return true;
    }

private:
    inline bool isNumber(char a)
    {
        if (a >= '0' && a <= '9')
            return true;
        return false;
    }

    inline bool getStringStartEnd(const char* s, int &start, int &end)
    {
        int len = 0;
        const char* curC = s;
        while (*curC != '\0')
        {
            len++;
            curC++;
        }

        for (start = 0; start < len && s[start] == ' '; start++){}
        if (start == len)   return false;

        for (end = len - 1; end >= 0 && s[end] == ' '; end--){}
        if (end < 0)   return false;

        return true;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    const char* s = "3";

    Solution so;
    so.isNumber(s);

	return 0;
}

