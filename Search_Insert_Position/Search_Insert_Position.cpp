// Search_Insert_Position.cpp : 定义控制台应用程序的入口点。
//

class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        if (n == 0) return 0;
        int start = 0, end = n - 1, mid = 0;
        while (start <= end){
            mid = ((start + end) >> 1);
            if (target == A[mid]) return mid;
            else if (target > A[mid]) start = mid + 1;
            else end = mid - 1;
        }
        if (start > end || target < A[start]) return start;
        return start + 1;
    }
};


int main()
{
	return 0;
}

