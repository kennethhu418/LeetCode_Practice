// Candy.cpp : 定义控制台应用程序的入口点。
//
/**********************************************************************************
    There are N children standing in a line.Each child is assigned a rating value.

    You are giving candies to these children subjected to the following requirements :

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.
    What is the minimum candies you must give ?
**********************************************************************************/

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();

        if (n == 0 || n == 1) return n;

        int total = 0;
        int nextAssignCandyChild = 0;
        int curValley = -1;
        int curChild = 1;
        int giveCandyNum = 1;
    
        while (true)
        {
            //First get valley
            while (curChild < n)
            {
                if (ratings[curChild] > ratings[curChild - 1])
                {
                    curValley = curChild - 1;
                    break;
                }

                curChild++;
            }

            if (curChild == n) //the ratings vector is a non-increasing array
                curValley = n - 1;

            total++;   //assign to the valley child
            giveCandyNum = 1;

            //move left in the children line
            curChild = curValley - 1;
            while (curChild >= nextAssignCandyChild)
            {
                if (ratings[curChild] > ratings[curChild + 1])
                {
                    giveCandyNum++;
                    total += giveCandyNum;
                }
                else
                {
                    assert(ratings[curChild] == ratings[curChild + 1]);
                    total += giveCandyNum;
                }

                curChild--;
            }

            //move right in the children line
            giveCandyNum = 1;
            curChild = curValley + 1;
            while (curChild < n)
            {
                if (ratings[curChild] > ratings[curChild - 1])
                {
                    giveCandyNum++;
                    total += giveCandyNum;
                    curChild++;
                }
                else if (ratings[curChild] == ratings[curChild - 1])
                {
                    total += giveCandyNum;
                    curChild++;
                }
                else
                {
                    nextAssignCandyChild = curChild;
                    break;
                }
            }

            if (curChild == n)
                break;

            curChild = nextAssignCandyChild + 1;
        } //end while(true)

        return total;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

