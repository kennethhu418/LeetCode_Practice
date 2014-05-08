// Word_Break.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using namespace tr1;

/*dynamic programming*/

class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        int n = s.size();

        if(n == 0)
            return false;

        bool *canBreakArr = new bool[n+1];
        memset(canBreakArr, 0 ,sizeof(bool)*n);
        canBreakArr[n] = true;

        string substr;
        int size;

        for(int i = n-1; i >= 0; i--)
        {
            size = n - i;

            for(int j = 0; j < size; j++)
            {
                substr.clear();
                substr = s.substr(i, j+1);

                if(dict.find(substr) == dict.end())
                    continue;

                if(canBreakArr[i+j+1])
                {
                    canBreakArr[i] = true;
                    break;
                }
            }
        }

        bool retVal = canBreakArr[0];
        delete [] canBreakArr;
        return retVal;        
    }
};


int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}

