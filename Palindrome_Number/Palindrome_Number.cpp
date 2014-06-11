// Palindrome_Number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;

        if (x <= 9)
            return true;

        int orgX = x;
        int reversedX = 0;
        while (x)
        {
            reversedX = reversedX * 10 + x % 10;
            x = x/10;
        }

        if (reversedX == orgX)
            return true;
        return false;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int     a;
    Solution so;

    while (cin >> a)
    {
        cout << so.isPalindrome(a) << endl;
    }

	return 0;
}
