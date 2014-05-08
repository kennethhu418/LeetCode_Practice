// Word_Break_II.cpp : Defines the entry point for the console application.
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
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        int n = s.size();
        vector<string> resultCollection;

        if(n == 0)
            return resultCollection;

        vector<string>*  stringBreakStore = new vector<string>[n+1];
        stringBreakStore[n].push_back("");

        string substr, res; int size, len;

        for(int i = n - 1; i >= 0; i--)
        {
            size = n - i;
            for(int j = 0; j < size; j++)
            {
                substr = s.substr(i, j+1);
                if(dict.find(substr) == dict.end())
                    continue;

                if(stringBreakStore[i+j+1].size() == 0)
                    continue;

                len = stringBreakStore[i+j+1].size();
                for(int k = 0; k < len; k++)
                {
                    res.clear();
                    res = substr;
					if(stringBreakStore[i+j+1].at(k).size() > 0)
					{
						res += " ";
						res += stringBreakStore[i+j+1].at(k);
					}
                    stringBreakStore[i].push_back(res);
                }
            }
        }

        size = stringBreakStore[0].size();
        for(int i = 0; i < size; i++)
            resultCollection.push_back(stringBreakStore[0].at(i));

        delete [] stringBreakStore;
        return resultCollection;     
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

