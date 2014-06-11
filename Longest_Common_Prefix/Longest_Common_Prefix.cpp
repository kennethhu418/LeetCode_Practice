// Longest_Common_Prefix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>

using std::string;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        string result;
        int n = strs.size();
        if (n == 0) return result;
        if (n == 1) return strs[0];

        int base_size = strs[0].size();

        for (int curPos = 0; curPos < base_size; curPos++)
        {
            for (int i = 1; i < n; i++)
            {
                if (strs[i].size() <= curPos || strs[i][curPos] != strs[0][curPos])
                    return result;
            }

            result += strs[0][curPos];
        }

        return result;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

