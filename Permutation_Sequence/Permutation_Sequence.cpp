// Permutation_Sequence.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        if (n == 0) return "";
        string result(n, '0');
        if (n == 1) {
            result[0] = '0' + k;
            return result;
        }

        --k; // 0 based index
        int base = 1, curIndex = 0;
        for (int i = 2; i < n; ++i) base *= i;
        for (int i = 0; i < n; ++i) result[i] = '1' + i;

        char target = '0';
        for (int i = 0; i < n - 1; ++i){
            curIndex = k / base;
            target = result[i + curIndex];
            for (int j = i + curIndex; j > i; --j) result[j] = result[j - 1];
            result[i] = target;

            k -= base * curIndex;
            base /= (n - 1 - i);
        }
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

