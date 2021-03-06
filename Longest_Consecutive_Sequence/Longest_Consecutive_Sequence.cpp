// Longest_Consecutive_Sequence.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_map>
#include <vector>


using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        int     n = num.size();
        if (n == 0 || n == 1)
            return n;

        unordered_map<int, bool>     hashA;
        for (int i = 0; i < n; i++)
        {
            hashA[num[i]] = false;  //has not been visited yet
        }

        int longestCount = 0; int  Len, val;
        for (int i = 0; i < n; i++)
        {
            if (hashA[num[i]] == true)
                continue;

            hashA[num[i]] = true;

            Len = 1;
            val = num[i] + 1;
            while (hashA.find(val) != hashA.end())
            {
                hashA[val] = true;
                Len++;
                val++;
            }

            val = num[i] - 1;
            while (hashA.find(val) != hashA.end())
            {
                hashA[val] = true;
                Len++;
                val--;
            }

            if (longestCount < Len)
                longestCount = Len;
        }

        return longestCount;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

