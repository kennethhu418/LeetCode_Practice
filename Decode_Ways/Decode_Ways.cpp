// Decode_Ways.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();

        if (n == 0) return n;

        if (s[0] == '0')
            return 0;

        if (n == 1)
            return n;

        int *countArr = new int[n + 1];
        countArr[n] = countArr[n - 1] = 1;
        if (s[n - 1] == '0') countArr[n - 1] = 0;

        for (int pos = n - 2; pos >= 0; pos--)
        {
            if (s[pos] == '0')
                countArr[pos] = 0;
            else
            {
                countArr[pos] = countArr[pos + 1];

                if (strToNum(s, pos, 2) < 27)
                    countArr[pos] += countArr[pos + 2];
            }
        }

        int retVal = countArr[0];
        delete[] countArr;
        return retVal;
    }

private:
    int strToNum(const string& s, int start, int characterCount)
    {
        int     num = 0;
        while (characterCount > 0)
        {
            num = num * 10 + s[start] - '0';
            start++;
            characterCount--;
        }

        return num;
    }

};

int _tmain(int argc, _TCHAR* argv[])
{
    string s = "0";

    Solution so;
    cout<<so.numDecodings(s)<<endl;

    system("PAUSE");
	return 0;
}

