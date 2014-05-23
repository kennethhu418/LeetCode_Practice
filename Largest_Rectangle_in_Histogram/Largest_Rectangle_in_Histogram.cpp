// Largest_Rectangle_in_Histogram.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <stack>
#include <assert.h>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        int     n = height.size();
        if (n == 0)
            return 0;

        if (n == 1)
            return height[0];

        /*data stack is to store each height. And the heights stored in the stack
         *are in non-decending order from bottom to top*/
        stack<int>  dataStack;
        /*Each element in width stack is corresponding to each height in data stack.
         * It records how many consecutive heights in the current height's left
         * side are smaller than the current height, so the current width means
         * how many width can the current height be extended to the left side
         * to form a rectangle.*/
        stack<int>  widthStack;
        int     maxRectArea = height[0];
        dataStack.push(height[0]);
        widthStack.push(1);
        int     originalLastHeight = height[n-1];
        int     curIndex = 1;
        bool  hasPushedEndData = false;
        int     curWidth = 0;
        int     curArea = 0;

        while (curIndex < n)
        {
            assert(!dataStack.empty());
            assert(!widthStack.empty());

            if (height[curIndex] >= dataStack.top())
            {
                dataStack.push(height[curIndex]);
                widthStack.push(1);
            }
            else
            {
                curWidth = 0;
                while (!dataStack.empty() && dataStack.top() > height[curIndex])
                {
                    assert(!widthStack.empty());
                    curWidth += widthStack.top();
                    curArea = curWidth*dataStack.top();
                    widthStack.pop();
                    dataStack.pop();
                    if (curArea > maxRectArea)
                        maxRectArea = curArea;
                }

                dataStack.push(height[curIndex]);
                widthStack.push((1 + curWidth));
            }

            if (!hasPushedEndData && curIndex + 1 == n)
            {
                height[curIndex] = 0;
                hasPushedEndData = true;
                continue;
            }

            curIndex++;
        }

        height[n - 1] = originalLastHeight;
        return maxRectArea;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}