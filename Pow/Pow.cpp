// Pow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>

using namespace std;

class Solution {
public:
    double pow(double x, int n) {
        if (n == 0) return 1;
        if (x == 0) return 0;
        if (x == 1) return 1;
        if (x == -1) return ((abs(n) & 1) ? -1 : 1);
        if (n == 1) return x;
        if (n == -1) return 1 / x;

        bool isNegative = (n < 0 ? true : false);
        n = (isNegative ? -n : n);

        int d = 0, mask = n;
        while (mask){
            mask >>= 1;
            ++d;
        }
        mask = (1 << (d - 1));

        double result = 1;
        while (mask > 0){
            result = result * result;
            result *= (mask & n) ? x : 1;
            mask >>= 1;
        }

        return isNegative ? 1 / result : result;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Solution    s;
    printf("%f\n\n", s.pow(10, -4));
	return 0;
}

