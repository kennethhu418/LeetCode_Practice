// Combinations.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> >    result;
        vector<int> singleComb;

        if (k > n || n < 1 || k == 0)  return result;
        if (n == 1)
        {
            assert(k == 1);
            singleComb.push_back(1);
            result.push_back(singleComb);
            return result;
        }

        vector<vector<int> >    *curRes = new   vector<vector<int> >[k];
        vector<vector<int> >    *prevRes = new   vector<vector<int> >[k];
        vector<vector<int> >    *temp;

        //the result of the last element
        singleComb.push_back(n);
        prevRes[0].push_back(singleComb);
        singleComb.clear();

        //Now traverse each number before the last one
        for (int i = n - 1; i >= 1; i--)
        {
            //k' = 1 case
            singleComb.push_back(i);
            curRes[0].push_back(singleComb);
            singleComb.clear();
            CopyFromVectorWithAdd(curRes[0], prevRes[0], 0, false);

            for (int j = 2; j <= n - i + 1 && j <= k; j++)
            {
                //not include i
                CopyFromVectorWithAdd(curRes[j - 1], prevRes[j - 1], 0, false);
                //include i
                CopyFromVectorWithAdd(curRes[j - 1], prevRes[j - 2], i, true);
            }

            temp = curRes;
            curRes = prevRes;
            prevRes = temp;
            for (int i = 0; i < k; i++)
                curRes[i].clear();
        }

        result = prevRes[k-1];
        delete[] curRes;
        delete[] prevRes;
        return result;
    }

private:
    inline void CopyFromVectorWithAdd(vector<vector<int> > & dest, vector<vector<int> > & src, int addVal, bool add)
    {
        int     n = src.size(), m = 0;
        vector<int> singleComb;

        for (int i = 0; i < n; i++)
        {
            if (!add)
            {
                dest.push_back(src[i]);
                continue;
            }

            singleComb.push_back(addVal);
            m = src[i].size();
            for (int j = 0; j < m; j++)
                singleComb.push_back(src[i][j]);

            dest.push_back(singleComb);
            singleComb.clear();
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    Solution    s;
    s.combine(2, 2);
	return 0;
}

