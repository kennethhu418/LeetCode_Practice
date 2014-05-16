// Distinct_Subsequences.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

//Dynamic Programming
class Solution {
public:
    int numDistinct(string S, string T) {
        int sizeS = S.size();
        int sizeT = T.size();

        if (sizeS == 0)
        {
            if (sizeT == 0)
                return 1;
            return 0;
        }

        if (sizeS < sizeT)
            return 0;

        int** resultArray = new int*[sizeT+1];
        for (int i = 0; i <= sizeT; i++)
        {
            resultArray[i] = new int[sizeS + 1];
            memset(resultArray[i], 0, sizeof(int)*(sizeS+1));
        }

        int s, t;

        for (s = sizeS - 1; s >= 0; s--)
        {
            if (T[sizeT - 1] == S[s])
                resultArray[sizeT - 1][s] = 1 + resultArray[sizeT - 1][s + 1];
            else
                resultArray[sizeT - 1][s] = resultArray[sizeT - 1][s + 1];
        }

        for (t = sizeT - 2; t >= 0; t--)
        {
            for (s = sizeS - 1; s >= 0; s--)
            {
                if (T[t] == S[s])
                    resultArray[t][s] = resultArray[t + 1][s + 1] + resultArray[t][s + 1];
                else
                    resultArray[t][s] = resultArray[t][s+1];
            }
        }

        int finalResult = resultArray[0][0];
        for (int i = 0; i <= sizeT; i++)
        {
            delete [] resultArray[i];
        }
        delete[]resultArray;
        return finalResult;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string S = "aabb";
    string T = "ab";

    Solution solution;
    printf("%d\n\n", solution.numDistinct(S, T));

    system("PAUSE");
	return 0;
}

