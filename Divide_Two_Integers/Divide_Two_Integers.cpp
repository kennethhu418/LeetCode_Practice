// Divide_Two_Integers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <algorithm>

using namespace std;

#define SIGN_MASK 0x80000000

//the first version did not consider that dividend or divisor may be 0xFFFFFFFF, in this case, there is no valid value of 0 - 0xFFFFFFFF, resulting in bad result.
class Solution {
public:
    int divide(int dividend, int divisor) {
        assert(divisor != 0);
        if (dividend == 0)  return 0;
        if (dividend == divisor) return 1;
        if (divisor == 1) return dividend;
        if (divisor == -1) return 0 - dividend;

        long long dividendT = dividend;
        long long divisorT = divisor;

        bool needChangeSign = (SIGN_MASK&dividend) ^ (SIGN_MASK&divisor);
        if (dividendT < 0)
            dividendT = 0 - dividendT;
        if (divisorT < 0)
            divisorT = 0 - divisorT;

        long long residule = 0;
        long long result = divide(dividendT, divisorT, residule);

        if (needChangeSign)
            result = 0 - result;
        return (int)result;
    }

private:
    long long divide(long long dividend, long long divisor, long long & r)
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

        long long result = divide(dividend >> 1, divisor, r);

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

