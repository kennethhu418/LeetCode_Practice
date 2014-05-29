// Length_of_Last_Word.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    int lengthOfLastWord(const char *s) {
        if (s == NULL || *s == '\0')
            return 0;

        int     wordStart = 0, wordEnd = 0;
        int     len = 0;

        do
        {
            wordStart = getFirstLetter(s, wordEnd);
            if (wordStart == -1)
                return len;

            wordEnd = getFirstSpace(s, wordStart + 1);

            len = wordEnd - wordStart;
        } while (s[wordEnd] != '\0');

        return len;       
    }

private:
    inline int getFirstLetter(const char* s, int start)
    {
        s = s + start;
        if (*s == '\0')
            return -1;

        while (*s != '\0')
        {
            if (*s != ' ')
                return start;
            start++;
            s++;
        }

        return -1;
    }

    inline int getFirstSpace(const char* s, int start)
    {
        s = s + start;
        if (*s == '\0')
            return start;

        while (*s != '\0')
        {
            if (*s == ' ')
                return start;
            start++;
            s++;
        }

        return start;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    const char* s = " test.  ";
    Solution so;
    
    printf("%d\n\n", so.lengthOfLastWord(s));

	return 0;
}