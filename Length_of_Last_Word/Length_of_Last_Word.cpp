// Length_of_Last_Word.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    int lengthOfLastWord(const char *s) {
        if (s == NULL || *s == '\0')
            return 0;

        const char* firstLetter = getNextLetter(s);

        int wordLen = 0;
        while (*firstLetter != '\0')
        {
            wordLen = 0;

            while (*firstLetter != '\0' && *firstLetter != ' ')
            {
                wordLen++;
                firstLetter++;
            }

            firstLetter = getNextLetter(firstLetter);
        }

        return wordLen;
    }

private:
    inline const char* getNextLetter(const char* s)
    {
        while (*s != '\0' && *s == ' ')
            s++;
        return s;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    const char* s = " test.  ";
    Solution so;
    
    printf("%d\n\n", so.lengthOfLastWord(s));

	return 0;
}