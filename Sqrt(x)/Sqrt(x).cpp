// Sqrt(x).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class Solution {
public:
    int sqrt(int n) 
    {
        if (n == 0) return 0;
        if (n < 4)  return 1;

        double x0 = n / 2 + 1;
        double y0 = x0 * x0 - n;

        while (y0 > 0.0001)
        {
            x0 = x0 - y0 / (2*x0);
            y0 = x0 * x0 - n;
        }

        return (int)x0;
    }
};

class Solution_BinarySearch {
public:
    int sqrt(int n)
    {
        if (n == 0) return 0;
        if (n < 4)  return 1;

        long long start = 2, end = n / 2 + 1, mid = 0;

        while (start < end)
        {
            mid = (start + end)/2;
            if (mid * mid == n)
                return mid;

            if (mid*mid < n)
                start = mid + 1;
            else
                end = mid - 1;
        }

        if (start*start > n)
            start--;

        return start;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int n = 3;
    Solution_BinarySearch so;

    std::cin >> n;
    while (n >= 0)
    {
        printf("%d\n\n", so.sqrt(n));
        std::cin >> n;
    }

	return 0;
}

