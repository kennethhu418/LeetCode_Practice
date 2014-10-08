// Subsets_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int> &S) {
        vector<vector<int>> resultArr;
        int n = S.size(); if (n == 0) return resultArr;

        vector<int> singleRes;
        resultArr.push_back(singleRes);
        sort(S.begin(), S.end());

        int curPos = 0, repeatCnt = 0, orgSize = 0;
        while (curPos < n){
            repeatCnt = getRepeatCnt(S, curPos);
            orgSize = resultArr.size();
            for (int i = 1; i <= repeatCnt; ++i)
                combineResult(resultArr, resultArr, orgSize, S[curPos], i);
            curPos += repeatCnt;
        }

        return resultArr;
    }

private:
    int getRepeatCnt(const vector<int> &S, int start){
        int cnt = 1, orgVal = S[start++];
        while (start < S.size() && S[start] == orgVal){
            ++start; ++cnt;
        }
        return cnt;
    }

    void combineResult(vector<vector<int>> &dest, const vector<vector<int>> &src, int size, int data, int cnt){
        vector<int> singleRes;
        for (int i = 0; i < size; ++i){
            singleRes = src[i];
            for (int j = 0; j < cnt; ++j) singleRes.push_back(data);
            dest.push_back(singleRes);
        }
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

