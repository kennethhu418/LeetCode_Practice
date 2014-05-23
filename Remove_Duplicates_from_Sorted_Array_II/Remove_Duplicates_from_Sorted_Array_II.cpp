// Remove_Duplicates_from_Sorted_Array_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n < 2)
            return n;

        int curStartPos = 0, curEndPos = 0, curPlacePos = 0, dupedNum = 0;

        while (curStartPos < n)
        {
            curEndPos = curStartPos;

            //Find duplicates
            while (curEndPos + 1 < n && A[curEndPos + 1] == A[curStartPos])
                curEndPos++;

            dupedNum = curEndPos - curStartPos + 1;

            if (curStartPos != curPlacePos)
            {
                A[curPlacePos] = A[curStartPos];
                if (dupedNum > 1)   A[curPlacePos + 1] = A[curStartPos];
            }

            curStartPos = curEndPos + 1;
            curPlacePos++;
            if (dupedNum > 1)   curPlacePos++;
        }

        return curPlacePos;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

