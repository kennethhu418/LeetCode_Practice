// Anagrams.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

#define sorted_string string

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        vector<string>  result;
        int n = strs.size();
        if (n < 2) return result;

        unordered_map<sorted_string, string> mapA;
        sorted_string sortedStr;
        int countBuffer[26];

        for (int i = 0; i < n; i++)
        {
            generateSortedStr(sortedStr, strs[i], countBuffer);
            if (mapA.find(sortedStr) == mapA.end())
                mapA[sortedStr] = strs[i];
            else
            {
                if (mapA[sortedStr] != "-*-&")
                {
                    result.push_back(mapA[sortedStr]);
                    mapA[sortedStr] = "-*-&";
                }
                
                result.push_back(strs[i]);
            }
        }

        return result;
    }

private:
    inline void generateSortedStr(sorted_string &result, const string& src, int* cntBuf)
    {
        memset(cntBuf, 0, 26*sizeof(int));

        result = "";

        for (int i = 0; i < src.size(); i++)
            cntBuf[src[i] - 'a']++;

        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < cntBuf[i]; j++)
                result += ('a' + i);
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

