// Divide_Two_Integers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

#define SIGN_MASK 0x80000000
#define MIN_INTEGER 0x80000000
//Here we made a little modification to the latest version, where we will not use "long long" but still stick to the "int" type
class Solution {
public:
    int divide(int dividend, int divisor) {
        assert(divisor != 0);
        if (dividend == 0)  return 0;
        if (dividend == divisor) return 1;
        if (divisor == 1) return dividend;
        if (divisor == -1) return 0 - dividend;
        if (divisor == MIN_INTEGER) return 0;

        unsigned int result = 0;
        bool needChangeSign = (SIGN_MASK&dividend) ^ (SIGN_MASK&divisor);

        if (divisor < 0)
            divisor = 0 - divisor;

        if (dividend < 0)
        {
            if (dividend == MIN_INTEGER)
            {
                dividend += divisor;
                result = 1;
            }

            dividend = 0 - dividend;
        }

        if (dividend < divisor)
            return result;

        unsigned int dividendT = dividend;
        unsigned int divisorT = divisor;

        int shiftCount = 0;
        unsigned int shiftedRes = divisorT;
        while (shiftedRes <= dividendT)
        {
            shiftCount++;
            shiftedRes = shiftedRes << 1;
        }
        shiftCount--;
        shiftedRes = shiftedRes >> 1;

        while (shiftCount >= 0)
        {
            if (shiftedRes <= dividendT)
            {
                result += (1 << shiftCount);
                dividendT -= shiftedRes;
            }                
          
            shiftCount--;
            shiftedRes = shiftedRes >> 1;
        }

        if (needChangeSign)
            return 0 - (int)result;
        return (int)result;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int dividend = -101;
    int divisor = 3;

    Solution so;
    int res = so.divide(dividend ,divisor);

    printf("%d\n\n", res);

	return 0;
}

