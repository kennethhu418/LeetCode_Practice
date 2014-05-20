// Unique_Binary_Search_Trees.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    int numTrees(int n) {
        if (n == 0 || n == 1)
            return 1;

        int*    BSTNum = new int[n+1];
        BSTNum[0] = BSTNum[1] = 1;

        for (int curNodeNum = 2; curNodeNum <= n; curNodeNum++)
        {
            BSTNum[curNodeNum] = 0;

            for (int k = 1; k <= curNodeNum; k++)
                BSTNum[curNodeNum] += (BSTNum[k - 1] * BSTNum[curNodeNum - k]);
        }

        int finalRes = BSTNum[n];
        delete[] BSTNum;
        return finalRes;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

