// Divide_Two_Integers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <algorithm>

using namespace std;

#define SIGN_MASK 0x80000000

class Solution {
public:
    int divide(int dividend, int divisor) {
        assert(divisor != 0);
        if (dividend == 0)  return 0;
        if (dividend == divisor) return 1;
        if (divisor == 1) return dividend;
        if (divisor == -1) return 0 - dividend;

        int dividendT = dividend;
        int divisorT = divisor;

        bool needChangeSign = (SIGN_MASK&dividend) ^ (SIGN_MASK&divisor);
        if (dividendT < 0)
            dividendT = 0 - dividendT;
        if (divisorT < 0)
            divisorT = 0 - divisorT;            

        int residule = 0;
        int result = divide(dividendT, divisorT, residule);

        if (needChangeSign)
            result = 0 - result;
        return (int)result;
    }

private:
    int divide(int dividend, int divisor, int & r)
    {
        if (dividend == divisor)
        {
            r = 0;
            return 1;
        }

        if (dividend < divisor)
        {
            r = dividend;
            return 0;
        }

        int result = divide(dividend >> 1, divisor, r);

        result += result;
        r += r;
        if (0x1 & dividend)
            r++;

        if (r >= divisor)
        {
            result++;
            r -= divisor;
        }

        return result;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int dividend = 101 ;
    int divisor = -3;

    Solution so;
    int res = so.divide(dividend ,divisor);

    printf("%d\n\n", res);

	return 0;
}

