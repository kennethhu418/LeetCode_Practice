// Single_Number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    int singleNumber(int A[], int n) {
        int result = 0;

        for (int i = 0; i < n; i++)
        {
            result = result^A[i];
        }

        return result;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

