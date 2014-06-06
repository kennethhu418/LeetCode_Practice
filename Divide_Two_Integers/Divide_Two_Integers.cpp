// Divide_Two_Integers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

#define SIGN_MASK 0x80000000
//The previous two versions have time complexity of O(log(dividend)), which is already acceptable. But it uses recursive function, it means consuming a lot of memory.
//So here we use another algorithm, which is described in "Algorithm.jpg" and whose complexity is O(log(result)) = O(log(dividend/divisor)) = O(log(dividend) - log(divisor))
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

        int shiftCount = 0;
        long long shiftedRes = divisorT;
        while (shiftedRes <= dividendT)
        {
            shiftCount++;
            shiftedRes = shiftedRes << 1;
        }
        shiftCount--;
        shiftedRes = shiftedRes >> 1;

        long long result = 0;
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
            result = 0 - result;

        return (int)result;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int dividend = 101 ;
    int divisor = 3;

    Solution so;
    int res = so.divide(dividend ,divisor);

    printf("%d\n\n", res);

	return 0;
}

