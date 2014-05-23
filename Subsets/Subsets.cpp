// Subsets.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        int     size = S.size();
        vector<vector<int>> resultArray;
        vector<int> singleSetElement;
        resultArray.push_back(singleSetElement);

        if (size == 0)
            return resultArray;

        sort(S.begin(), S.end());

        for (int i = size - 1; i >= 0; i--)
        {
            for (int j = resultArray.size() - 1; j >= 0; j--)
            {
                singleSetElement.clear();
                CopyPrevResultWithAddingElem(singleSetElement, S[i], resultArray[j]);
                resultArray.push_back(singleSetElement);
            }
        }

        return resultArray;
    }

private:
    inline void CopyPrevResultWithAddingElem(vector<int> &dest, int val, const vector<int> &src)
    {
        int size = src.size();
        dest.push_back(val);

        for (int i = 0; i < size; i++)
            dest.push_back(src[i]);
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

