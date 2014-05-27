// Minimum_Window_Substring.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <assert.h>
using namespace std;

class Solution {
public:
    string minWindow(string S, string T) {
        int SSize = S.size(), TSize = T.size();

        if (SSize == 0 || TSize == 0)
            return "";

        int*    lookupTable = new int[256];
        memset(lookupTable, 0 , 256*sizeof(int));

        int targetCharNum = constructLookupTable(lookupTable, T);

        int*    dynamicTable = new int[256];
        memset(dynamicTable, 0, 256 * sizeof(int));
        int     start = 0, end = 0, targetCharsInRange = 0;

        while (start < SSize)
        {
            if (lookupTable[S[start]])
                break;
            start++;
        }

        if (start == SSize)
        {
            delete[] lookupTable;
            delete[] dynamicTable;
            return "";
        }

        end = start;  dynamicTable[S[start]]++;   targetCharsInRange = lookupTable[S[start]] == 1 ? 1 : 0;
        findFullTargetCharsRange(S, start, end, dynamicTable, lookupTable, targetCharsInRange, targetCharNum);
        if (targetCharsInRange < targetCharNum)
        {
            delete[] lookupTable;
            delete[] dynamicTable;
            return "";
        }

        int minStart = start, minEnd = end;
        RemoveCharInStart(S, start, end, dynamicTable, lookupTable, targetCharsInRange);
        while (start < SSize)
        {
            findFullTargetCharsRange(S, start, end, dynamicTable, lookupTable, targetCharsInRange, targetCharNum);
            if (targetCharsInRange < targetCharNum)
                break;

            if (end - start < minEnd - minStart)
            {
                minStart = start; minEnd = end;
            }

            RemoveCharInStart(S, start, end, dynamicTable, lookupTable, targetCharsInRange);
        }

        delete[] lookupTable;
        delete[] dynamicTable;
        return  S.substr(minStart, minEnd - minStart + 1);
    }

private:
    inline int constructLookupTable(int* lookupTable, const string& T)
    {
        int     n = T.size();
        int     num = 0;
        for (int i = 0; i < n; i++)
        {
            if (lookupTable[T[i]] == 0)
                num++;
            lookupTable[T[i]]++;
        }
        return num;            
    }

    inline void findFullTargetCharsRange(const string& S, int &start, int &end, int* dynamicTable, const int* lookupTable, int& targetCharsInRange, int targetCharNum)
    {
        if (targetCharsInRange == targetCharNum)
            return;

        int     n = S.size();
        end++;
        while (end < n)
        {
            if (lookupTable[S[end]] == 0)
            {
                end++;  continue;
            }

            dynamicTable[S[end]]++;
            if (dynamicTable[S[end]] == lookupTable[S[end]])
                targetCharsInRange++;
            if (targetCharsInRange == targetCharNum)
                return;

            end++;
        }
    }

    inline void RemoveCharInStart(const string& S, int &start, int &end, int* dynamicTable, const int* lookupTable, int& targetCharsInRange)
    {
        dynamicTable[S[start]]--;
        if (dynamicTable[S[start]] < lookupTable[S[start]])
            targetCharsInRange--;

        if (start == end)
        {
            start++;
            while(start < S.size())
            { 
                if (lookupTable[S[start]])
                    break;
                start++;
            }

            end = start;
            return;
        }

        int curStart = start + 1;
        while (start <= end)
        {
            if (lookupTable[S[curStart]])
                break;
            curStart++;
        }

        assert(curStart <= end);
        start = curStart;
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    string  S = "aa", T = "aa";
    string result;

    Solution    so;
    result = so.minWindow(S, T);

    printf("%s\n\n", result.c_str());

    system("PAUSE");
	return 0;
}