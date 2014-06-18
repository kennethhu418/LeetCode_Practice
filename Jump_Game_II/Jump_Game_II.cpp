// Jump_Game_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define   MAX_STEPS  0x7EFFFFFF

//Time complexity: O(n^2), resulting in TLE
class Solution {
public:
    int jump(int A[], int n) {
        if (n < 2)
            return 0;

        int* jumpSteps = new int[n];
        int   minStep = 0;
        jumpSteps[n - 1] = 0;

        for (int curPos = n - 2; curPos >= 0; curPos--)
        {
            if (A[curPos] == 0)
            {
                jumpSteps[curPos] = MAX_STEPS;
                continue;
            }

            minStep = MAX_STEPS;
            for (int step = 1; step <= A[curPos]; step++)
            {
                if (step + curPos > n - 2)
                {
                    minStep = 1;
                    break;
                }
                if (jumpSteps[step + curPos] + 1 < minStep)
                {
                    minStep = jumpSteps[step + curPos] + 1;
                }
            }

            jumpSteps[curPos] = minStep;
        }

        minStep = jumpSteps[0] >= MAX_STEPS ? -1 : jumpSteps[0];
        delete[] jumpSteps;
        return minStep;
    }
};

//Time Complexity: O(n)
class Solution2 {
public:
    int jump(int A[], int n) {
        if (n < 2)
            return 0;

        int curRangeStart = 0, curRangeEnd = 0;
        int curSteps = 0;
        int maxRangeEnd = 0;

        while (curRangeEnd < n)
        {
            maxRangeEnd = -1;

            for (int curPos = curRangeStart; curPos <= curRangeEnd; curPos++)
            {
                if (curPos + A[curPos] > n - 2)
                    return curSteps + 1;

                if (curPos + A[curPos] > maxRangeEnd)
                    maxRangeEnd = curPos + A[curPos];
            }

            curRangeStart = curRangeEnd + 1;
            curRangeEnd = maxRangeEnd;
            curSteps++;

            if (curRangeEnd < curRangeStart)
                return -1;
        }

        return -1;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

