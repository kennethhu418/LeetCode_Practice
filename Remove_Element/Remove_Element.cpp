// Remove_Element.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>

class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        if (n == 0) return 0;
        if (n == 1)
        {
            if (A[0] == elem)   return 0;
            return 1;
        }

        int start = 0, end = n - 1;
        while (start < end)
        {
            if (A[start] == elem)
            {
                while (end > start && A[end] == elem)
                    end--;
                if (end == start)
                    break;
                std::swap(A[start], A[end]);
            }

            start++;
        }

        if (A[start] == elem)
            return start;
        return start + 1;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

