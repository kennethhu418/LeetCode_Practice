// Pow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>

using namespace std;

class Solution {
public:
    double pow(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return x;
        if (x == 0) return 0;

        int n1 = abs(n);
        double d = abs(x);

        double result = pow_nonrecursive(d, n1);
        if (x < 0 && n & 0x1)
            result = 0 - result;

        if (n >= 0)
            return result;
        else
            return 1.0 / result;
    }

private:
    stack<int>  stackA;

    double pow_recursive(double x, int n)
    {
        int half = n / 2;
        double halfResult = pow(x, half);
        if (n & 0x1)
            return halfResult*halfResult*x;
        return halfResult*halfResult;
    }

    double pow_nonrecursive(double x, int n)
    {
        while (n > 1)
        {
            stackA.push(n);
            n = n / 2;
        }

        double retResult = x;
        while (!stackA.empty())
        {
            n = stackA.top();
            stackA.pop();

            if (n & 0x1)
                retResult = retResult*retResult*x;
            else
                retResult = retResult*retResult;
        }

        return retResult;        
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Solution    s;
    printf("%f\n\n", s.pow(10, -4));
	return 0;
}

