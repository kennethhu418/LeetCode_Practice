// Jump_Game.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//Time complexity: O(n^2), resulting in TLE
class Solution {
public:
    bool canJump(int A[], int n) {
        return canJump_recursive(A, 0, n);
    }

    bool canJump_recursive(int A[], int curPos, int n)
    {
        if (curPos >= n - 1)
            return true;

        if (A[curPos] == 0)
            return false;

        if (A[curPos] + curPos >= n - 1)
            return true;

        for (int step = 1; step <= A[curPos]; step++)
        {
            if (canJump_recursive(A, curPos + step, n))
                return true;
        }

        return false;
    }

    bool canJump_nonrecursive(int A[], int n) {
        if (n < 2)  return true;

        bool*   canJumpArr = new bool[n];
        canJumpArr[n - 1] = true;
        int step;

        for (int curPos = n - 2; curPos >= 0; curPos--)
        {
            for (step = A[curPos]; step >= 0; step--)
            {
                if (step + curPos >= n - 1 || canJumpArr[step + curPos])
                    break;
            }
            canJumpArr[curPos] = (step > A[curPos] ? false : true);
        }

        bool finalRes = canJumpArr[0];
        delete[] canJumpArr;
        return finalRes;
    }
};

class Solution2 {
public:
    bool canJump(int A[], int n) {
        if (n < 2)
            return true;

        int curRangeStart = 0, curRangeEnd = 0;
        int curSteps = 0;
        int maxRangeEnd = 0;

        while (curRangeEnd < n)
        {
            maxRangeEnd = -1;

            for (int curPos = curRangeStart; curPos <= curRangeEnd; curPos++)
            {
                if (curPos + A[curPos] > n - 2)
                    return true;

                if (curPos + A[curPos] > maxRangeEnd)
                    maxRangeEnd = curPos + A[curPos];
            }

            curRangeStart = curRangeEnd + 1;
            curRangeEnd = maxRangeEnd;
            curSteps++;

            if (curRangeEnd < curRangeStart)
                return false;
        }

        return false;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    return 0;
}

