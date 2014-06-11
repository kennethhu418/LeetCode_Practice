// Longest_Palindromic_Substring.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <assert.h>

using std::string;

class Solution {
public:
    string longestPalindrome(const string &s) {
        int n = s.size();
        if (n < 2)  return s;

        AllocateMemory(n);

        int len = 1;
        int maxLen = 1, maxStart = 0, maxEnd = 0;

        while (len <= n)
        {
            for (int curPos = 0; curPos <= n - len; curPos++)
            {
                if (s[curPos] != s[curPos + len - 1])
                    continue;

                if (len < 3)
                    palArray[curPos][curPos + len - 1] = true;
                else if(palArray[curPos + 1][curPos + len - 2])
                    palArray[curPos][curPos + len - 1] = true;

                if (palArray[curPos][curPos + len - 1] == true && len > maxLen)
                {
                    maxLen = len;  maxStart = curPos; maxEnd = curPos + len - 1;
                }
            }

            len++;
        }

        DestroyMemory();
        return s.substr(maxStart, maxLen);
    }

private:
    bool**  palArray;
    char*   buffer;

    void AllocateMemory(int n)
    {
        if (n == 0) return;

        int lineSize = n*sizeof(bool);
        buffer = new char[n*lineSize + n*sizeof(bool*)];
        assert(buffer);

        memset(buffer, 0, n*lineSize + n*sizeof(bool*));

        palArray = (bool**)(buffer + n*lineSize);
        for (int i = 0; i < n; i++)
            palArray[i] = (bool*)(buffer + i*lineSize);
    }

    void DestroyMemory()
    {
        delete[] buffer;
    }

};

int _tmain(int argc, _TCHAR* argv[])
{
    Solution so;

    string srcStr;
    
    while (std::cin >> srcStr)
    {
        std::cout << so.longestPalindrome(srcStr) << std::endl<<std::endl;
    }

	return 0;
}

