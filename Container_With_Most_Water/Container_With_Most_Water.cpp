// Container_With_Most_Water.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int maxArea(vector<int> &height) {
        int n = height.size();

        if (n < 2)
            return 0;

        int maxAreaVal = 0;

        int start = 0, end = n - 1, curArea;

        while (start < end)
        {
            if (height[start] < height[end])
            {
                curArea = (end - start)*height[start];
                start++;
            }
            else
            {
                curArea = (end - start)*height[end];
                end--;
            }

            if (curArea > maxAreaVal)
                maxAreaVal = curArea;            
        }

        return maxAreaVal;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int heightArr[] = {1, 2, 1};
    vector<int> heights(heightArr, heightArr + sizeof(heightArr)/sizeof(int));

    Solution so;
    std::cout << so.maxArea(heights) << std::endl;

    system("PAUSE");
	return 0;
}

