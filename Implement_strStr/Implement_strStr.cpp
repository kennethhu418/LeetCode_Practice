// Implement_strStr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        if (haystack == NULL || needle == NULL) return NULL;

        //first version did not consider corner cases:
        //what if haystack or needle is empty string.
        if (*needle == '\0')
        {
            return haystack;
        }

        char* curStart = haystack, *curPos = NULL, *curNeedle = needle, *nextStart = NULL;
        while (*curStart != '\0')
        {
            curNeedle = needle;
            curPos = curStart;

            while (*curPos != '\0' && *curNeedle != '\0' && *curPos == *curNeedle)
            {
                if (curStart != curPos && *curPos == *needle && nextStart == NULL)
                    nextStart = curPos;
                curPos++; curNeedle++;
            }

            if (*curPos == '\0' && *curNeedle == '\0')
                return curStart;
            if (*curPos == '\0')
                return NULL;
            if (*curNeedle == '\0')
                return curStart;

            if (nextStart != NULL)
                curStart = nextStart;
            else if (*curPos == *needle)
                curStart = curPos;
            else
                curStart = curPos + 1;
            nextStart = NULL;
        }

        return NULL;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    char* haystack = "aaaaaaa";
    char* needle = "aa";

    Solution so;
    char* result = so.strStr(haystack, needle);

	return 0;
}

