// Gray_Code.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> resultA;
        if (n == 0)
            return resultA;

        resultA.push_back(0);
        resultA.push_back(1);

        int     highestBitNum = 0;

        for (int i = 2; i <= n; i++)
        {
            highestBitNum = 0x1 << (i - 1);
            int size = resultA.size();

            for (int j = size - 1; j >= 0; j--)
                resultA.push_back(resultA[j] + highestBitNum);
        }

        return resultA;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

