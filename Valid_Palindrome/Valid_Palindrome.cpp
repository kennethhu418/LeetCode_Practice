// Valid_Palindrome.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int end = s.size() - 1;
        int start = 0;
        char rs, re;

        if (s.size() == 0)
            return true;

        while (start < end)
        {
            while (start < end && !isCharacter(s[start], rs))
                start++;
            if (start == end)
                return true;

            while (start < end && !isCharacter(s[end], re))
                end--;
            if (start == end)
                return true;

            if (rs != re)
                return false;

            start++; end--;
        }

        return true;
    }

private:
    inline bool isCharacter(char c, char &result)
    {
        if (c >= 'a' && c <= 'z'
            || c >= 'A' && c <= 'Z')
        {
            if (c >= 'A' && c <= 'Z')
                result = c + 'a' - 'A';
            else
                result = c;

            return true;
        }
        else if (c >= '0' && c <= '9')
        {
            result = c;
            return true;
        }

        return false;
    }

};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

