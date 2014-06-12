// Longest_Substring_Without_Repeating_Characters.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using std::string;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        if (n < 2) return n;

        int curRangeLen = 0;
        this->maxLen = 0;

        InvalidateArray();

        for (int i = 0; i < n; i++)
        {
            if (posAccArray[s[i]] < 0)
            {
                posAccArray[s[i]] = i;
                curRangeLen++;
                if (curRangeLen > maxLen)
                {
                    maxLen = curRangeLen;
                    maxLenPos = i - maxLen + 1;
                }                    
                continue;
            }

            InvalidateArray(s, i - curRangeLen, posAccArray[s[i]] - 1);
            curRangeLen = i - posAccArray[s[i]];
            posAccArray[s[i]] = i;
        }

        return this->maxLen;
    }

private:
    int       posAccArray[256];
    int       maxLen;
    int       maxLenPos;

    inline void InvalidateArray(const string& s = "", int start = 0, int end = 255)
    {
        if (s == "")
        {
            memset(&posAccArray[0], 0xFF, 256*sizeof(int));
            return;
        }
        if (end < start)
            return;

        for (int i = start; i <= end; i++)
            posAccArray[s[i]] = -1;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;

    string inputS;
    Solution    so;

    while (cin >> inputS)
    {
        cout << so.lengthOfLongestSubstring(inputS) << endl<<endl;
    }

	return 0;
}

