// Remove_Duplicates_from_Sorted_Array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n == 0 || n == 1)
            return n;

        int curStartPos = 0, curEndPos = 0, curPlacePos = 0;
        while (curStartPos < n)
        {
            curEndPos = curStartPos;

            //Find duplicates
            while (curEndPos + 1 < n && A[curEndPos + 1] == A[curStartPos])
                curEndPos++;

            if (curPlacePos != curStartPos)
                A[curPlacePos] = A[curStartPos];

            curPlacePos++;
            curStartPos = curEndPos + 1;
        }

        return curPlacePos;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

