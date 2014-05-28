// Permutation_Sequence.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        string  result = "";
        if (n == 0 || k == 0) return result;
        if (n == 1) return "1";

        int *   countHolder = new int[n + 1];
        bool *   isUsed = new bool[n+1];
        memset(isUsed, 0 , sizeof(bool)*(n+1));

        countHolder[0] = countHolder[1] = 1;
        for (int i = 2; i <= n; i++)
            countHolder[i] = (i - 1)*countHolder[i - 1];

        if (k > n*countHolder[n])
        {
            delete[] countHolder;
            delete[] isUsed;
            return "";
        }

        int curNum = 0, curIndex = 0, j, i;
        for (i = n; i >= 1; i--)
        {
            curNum = (k - 1) / countHolder[i];
            k = k - curNum*countHolder[i];
            curNum++;

            curIndex = 0;
            for (j = 1; j <= n; j++)
            {
                if (isUsed[j])
                    continue;
                curIndex++;
                if (curIndex == curNum)                    
                    break;
            }
            assert(j <= n);
            isUsed[j] = true;

            result += (j + '0');
        }

        delete[] isUsed;
        delete[] countHolder;
        return result;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    Solution so;
    string result;

    int n, k;
    cout << "n: ";
    cin >> n;
    cout << "k: ";
    cin >> k;

    while (n >= 0)
    {
        result = so.getPermutation(n, k);
        cout << result.c_str() << endl<<endl;

        cout << "n: ";
        cin >> n;
        cout << "k: ";
        cin >> k;
    }

	return 0;
}

