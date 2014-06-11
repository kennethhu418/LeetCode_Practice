// Container_With_Most_Water.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
    Solution()    {       top = 0;    }

    int maxArea(vector<int> &height) {
        int n = height.size();

        if (n < 2)  return 0;

        int maxWater = -1, curHeight = 0, curCount = 0;
        heightStack.push_back(height[0]);
        countStack.push_back(0);
        top = 1;

        for (int i = 1; i < n; i++)
        {
            if (height[i] < heightStack[top - 1])
            {
                heightStack.push_back(height[i]);
                countStack.push_back(1);
                top++;
                if (height[i] > maxWater)
                    maxWater = height[i];
                continue;
            }

            curHeight = std::min(height[i], heightStack[0]);
            curCount = 1;
            while (top > 0 && heightStack[top - 1] < height[i])
            {
                curCount += countStack[top - 1];
                heightStack.pop_back();
                countStack.pop_back();
                top--;
            }

            heightStack.push_back(height[i]);
            if (top > 0)
                countStack.push_back(curCount);
            else
                countStack.push_back(0);
            top++;

            if (curCount*curHeight > maxWater)
                maxWater = curCount*curHeight;
        }

        Reset();
        return maxWater;
    }

private:
    vector<int> heightStack;
    vector<int> countStack;
    int top;

    inline void Reset()
    {
        heightStack.clear();
        countStack.clear();
        top = 0;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int heightArr[] = {2, 3, 2, 4, 8, 3};
    vector<int> heights(heightArr, heightArr + sizeof(heightArr)/sizeof(int));

    Solution so;
    std::cout << so.maxArea(heights) << std::endl;

    system("PAUSE");
	return 0;
}

