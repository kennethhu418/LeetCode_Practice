// Valid_Number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstring>
#include <ctype.h>

class Solution {
public:
    bool isNumber(const char *s) {
        // deal with ' ' and (+-)
        while (*s == ' ')
            ++s;
        if (*s == '-' || *s == '+')
            ++s;
        int len = strlen(s);
        while (s[len - 1] == ' ')
            --len;
        if (len <= 0)
            return false;
        // look for 'e'
        const char *ptr = strchr(s, 'e');
        if (ptr) {
            int len1 = ptr - s;
            int len2 = len - len1 - 1;
            if (*(ptr + 1) == '+' || *(ptr + 1) == '-') {
                ++ptr;
                --len2;
            }
            return (isFnum(s, len1) && isDnum(ptr + 1, len2));
        }
        else
            return isFnum(s, len);
    }

    bool isFnum(const char *s, int len) {
        //		cout << "f" << s << endl << len << endl;
        // look for '.'
        const char *ptr = strchr(s, '.');
        if (ptr) {
            if (ptr - s == 0)
                return isDnum(s + 1, len - 1);
            if (ptr - s == len - 1)
                return isDnum(s, len - 1);
            else
                return (isDnum(s, ptr - s)
                && isDnum(ptr + 1, len - (ptr - s) - 1));
        }
        else
            return isDnum(s, len);
    }

    bool isDnum(const char *s, int len) {
        if (!len) return false;
        //		cout << "d" << s << endl << len << endl;

        const char *p = s;
        for (int i = 0; i < len; ++i, ++p) {
            if (!isdigit(*p))
                return false;
        }
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

