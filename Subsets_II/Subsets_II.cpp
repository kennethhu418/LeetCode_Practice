// Subsets_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int>>	subsetCollection;
        vector<int>	singleSubSet;
        subsetCollection.push_back(singleSubSet);

        if (S.size() == 0)
            return subsetCollection;

        sort(S.begin(), S.end());

        int	numCount = S.size();

        for (int i = numCount - 1; i >= 0; i--)
        {
            int prevSize = subsetCollection.size();

            int curStop = i - 1;
            while (curStop >= 0 && S[i] == S[curStop])
                curStop--;

            int sameCount = i - curStop;
            int repeatNum;

            for (int j = 0; j < prevSize; j++)
            {
                repeatNum = sameCount;
                while (repeatNum)
                {
                    singleSubSet.clear();
                    for (int k = 0; k < repeatNum; k++)
                        singleSubSet.push_back(S[i]);
                    CopySet(singleSubSet, subsetCollection[j]);
                    subsetCollection.push_back(singleSubSet);
                    repeatNum--;
                }
            }

            i = curStop + 1;
        }

        return subsetCollection;
    }

private:
    inline void CopySet(vector<int> &dest, const vector<int>& src)
    {
        for (int i = 0; i < src.size(); i++)
            dest.push_back(src.at(i));
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

