// N-Queens_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

typedef unsigned long long BOARDMASK;

class Solution {
private:
    int mTotalSolutions;
    BOARDMASK mFullMask;

    void totalNQueens(BOARDMASK colLimitMask, BOARDMASK diagLimitMask1, BOARDMASK diagLimitMask2)
    {
        if (colLimitMask == mFullMask){
            ++mTotalSolutions; return;
        }

        BOARDMASK allowedColMask = mFullMask & ~(colLimitMask | diagLimitMask1 | diagLimitMask2);
        BOARDMASK curColMask = 0;
        while (allowedColMask){
            curColMask = (allowedColMask & (1 + ~allowedColMask));
            totalNQueens(colLimitMask | curColMask, (diagLimitMask1 | curColMask) << 1, (diagLimitMask2 | curColMask) >> 1);
            allowedColMask ^= curColMask;
        }
    }

public:
    unsigned long long totalNQueens(int n) {
        if (n < 2) return n;

        mTotalSolutions = 0;
        BOARDMASK colLimitMask = 0, diagLimitMask1 = 0, diagLimitMask2 = 0;
        mFullMask = (1 << n) - 1;
        totalNQueens(colLimitMask, diagLimitMask1, diagLimitMask2);
        return mTotalSolutions;
    }
};

int main()
{
    Solution so;
    for (int n = 1; n < 31; ++n)
        std::cout << n << "-Queens solution count is " << so.totalNQueens(n) << std::endl;
    return 0;
}