// Reverse_Integer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MAX_INT    0x7FFFFFFF
#define MIN_INT    0x80000000

class Solution {
public:
    int reverse(int x) {
        if (x < 10 && x > -10)
            return x;

        if (x == MIN_INT)
            return x;

        unsigned int result = 0, r;
        int originalVal = x;
        bool isNegative = false;
        if (x < 0)
        {
            isNegative = true;
            x = 0 - x;
        }

        while (x)
        {
            if (result > MAX_INT / 10)
                return originalVal;

            result *= 10;
            r = x % 10;
            x = x / 10;

            if (result > MAX_INT - r)
                return originalVal;

            result += r;
        }

        if (!isNegative)
            return result;
        return 0 - (int)result;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

