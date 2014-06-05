// Trapping_Rain_Water.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trap(int A[], int n) {
        if (n < 3)
            return 0;


        stackHeight.push_back(A[0]);
        stackCount.push_back(1);
        int curPos = 1;
        int top = 1;
        int curHeight;
        int totalWater = 0, dupCount = 0;
        while (curPos < n)
        {
            if (A[curPos] == stackHeight[top - 1])
                stackCount[top - 1]++;
            else if (A[curPos] < stackHeight[top - 1])
            {
                stackHeight.push_back(A[curPos]);
                stackCount.push_back(1);
                top++;
            }
            else
            {
                curHeight = min(A[curPos], stackHeight[0]);
                dupCount = 0;
                while (top > 0 && stackHeight[top - 1] <= A[curPos])
                {
                    totalWater += (curHeight - stackHeight[top - 1])*stackCount[top - 1];
                    dupCount += stackCount[top - 1];
                    stackHeight.pop_back();
                    stackCount.pop_back();
                    top--;                    
                }

                stackHeight.push_back(A[curPos]);
                stackCount.push_back(dupCount + 1);
                top++;
            }

            curPos++;
        }

        stackCount.clear();
        stackHeight.clear();
        return totalWater; 
    }

private:
    vector<int> stackHeight;
    vector<int> stackCount;

};


int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = { 5, 5, 1, 7, 1, 1, 5, 2, 7, 6 };
    int n = sizeof(A) / sizeof(int);

    Solution so;
    so.trap(A, n);
	return 0;
}

