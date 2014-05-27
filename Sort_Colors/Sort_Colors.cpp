// Sort_Colors.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

using namespace std;

class Solution {
public:
    void sortColors(int A[], int n) 
    {
        if (n < 2)  return;

        int curPos0 = 0, curPos1 = -1, curPos2 = n - 1;
        while (curPos0 <= curPos2)
        {
            if (A[curPos0] == 0)
            {
                if (curPos1 >= 0)
                {
                    assert(curPos1 < curPos0);
                    swap(A, curPos1, curPos0);
                    curPos1++;
                    if (A[curPos1] != 1)
                        curPos1 = -1;
                }
                curPos0++;
                continue;
            }

            if (A[curPos0] == 1)
            {
                if (curPos1 < 0)
                    curPos1 = curPos0;
                curPos0++;
                continue;
            }

            assert(A[curPos0] == 2);
            while (curPos2 > curPos0 && A[curPos2] == 2)
                curPos2--;

            if (curPos2 == curPos0)
                break;

            swap(A, curPos0, curPos2);
        }

        return;
    }

private:
    inline void swap(int A[], int n1, int n2)
    {
        A[n1] ^= A[n2];
        A[n2] ^= A[n1];
        A[n1] ^= A[n2];
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int     A[] = {2, 0, 1, 1, 2, 0, 0, 1, 2, 2, 1, 1, 1, 0, 1, 2, 2, 0, 1};
    int     N = 19;

    Solution    so;
    so.sortColors(A, N);

	return 0;
}