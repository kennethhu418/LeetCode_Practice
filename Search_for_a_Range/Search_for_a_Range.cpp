// Search_for_a_Range.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> resultArr(2);
        resultArr[0] = resultArr[1] = -1;

        int startIndex = searchEdge(A, n, target);
        if (startIndex == -1) return resultArr;

        int endIndex = searchEdge(A, n, target, false);
        resultArr[0] = startIndex; resultArr[1] = endIndex;
        return resultArr;
    }

private:
    int searchEdge(int A[], int n, int target, bool searchLeftEdge = true){
        int start = 0, end = n - 1, mid = 0;
        while (start <= end){
            mid = ((start + end) >> 1);
            if (target == A[mid]){
                if (searchLeftEdge){
                    if (mid - 1 < start || A[mid - 1] != target) return mid;
                    end = mid - 1;
                }
                else {
                    if (mid + 1 > end || A[mid + 1] != target) return mid;
                    start = mid + 1;
                }
            }
            else if (target > A[mid]) start = mid + 1;
            else end = mid - 1;
        }
        return -1;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

