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
#include <iostream>
#include <vector>
#include <assert.h>
#include <time.h>

using namespace std;

#define MAX_INT 0x7FFFFFFF
#define MIN_INT 0x80000000

#define MAX_RATING 0x7FFFFFFF
#define MIN_RATING 0x80000000

class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();

        int high1 = 0, high2 = 0, low = 0;
        int totalCandy = 0, high1PrevCount = 0;
        int curCandyCount = 0, curChild = 0;

        low = getNextLow(ratings, 0);
        while (low < n)
        {
            high2 = getNextHigh(ratings, low + 1);

            //lowest child gets 1 candy
            curCandyCount = 1;
            totalCandy += curCandyCount;
            curChild = low - 1;

            //left children
            while (curChild >= high1)
            {
                if (ratings[curChild] == ratings[curChild + 1])
                    curCandyCount = 1;
                else
                    curCandyCount++;

                if (curChild == high1)
                {
                    if (curCandyCount > high1PrevCount)
                        totalCandy = totalCandy - high1PrevCount + curCandyCount;
                }
                else
                    totalCandy += curCandyCount;

                curChild--;
            }

            //right children
            curChild = low + 1;
            curCandyCount = 1;
            while (curChild < n && curChild <= high2)
            {
                if (ratings[curChild] == ratings[curChild - 1])
                    curCandyCount = 1;
                else
                    curCandyCount++;

                totalCandy += curCandyCount;
                if (high2 == curChild)
                    high1PrevCount = curCandyCount;

                curChild++;
            }

            low = getNextLow(ratings, high2 + 1);
            high1 = high2;
        }

        return totalCandy;
    }


private:
    inline int getNextLow(const vector<int> &ratings, int start)
    {
        int leftVal, rightVal, n = ratings.size();
        while (start < n)
        {
            leftVal = start > 0 ? ratings[start - 1] : MAX_RATING;
            rightVal = start <  n - 1 ? ratings[start + 1] : MAX_RATING;

            if (ratings[start] <= leftVal && ratings[start] < rightVal)
                return start;

            start++;
        }
        return n;
    }

    inline int getNextHigh(const vector<int> &ratings, int start)
    {
        int leftVal, rightVal, n = ratings.size();
        while (start < n)
        {
            leftVal = start > 0 ? ratings[start - 1] : MIN_RATING;
            rightVal = start <  n - 1 ? ratings[start + 1] : MIN_RATING;

            if (ratings[start] >= leftVal && ratings[start] > rightVal)
                return start;

            start++;
        }
        return n;
    }
};

void GenerateArray(vector<int> &ratings, int max_range)
{
    int n = ratings.size();

    for (int i = 0; i < n; i++)
        ratings[i] = rand() % max_range + 1;
}

void OutputArray(vector<int> &ratings)
{
    int n = ratings.size();

    for (int i = 0; i < n; i++)
        cout << ratings[i] << " ";
}

int _tmain(int argc, _TCHAR* argv[])
{
    const int CHILDREN_COUNT = 8;
    const int RATING_RANGE = 5;

    vector<int> ratings(CHILDREN_COUNT);
    char sig[30];
    Solution so;
    int result = -1;

    srand((unsigned int)time(NULL));

    while (cin >> sig)
    {
        if (*sig == 'N' || *sig == 'n' || result < 0)
        {
            cout << "Generate New Rating Array." << endl;
            GenerateArray(ratings, RATING_RANGE);
        }
        else
            cout << "Use last Rating Array." << endl;

        cout << "Rating Array is:" << endl;
        OutputArray(ratings);   cout << endl;

        result = so.candy(ratings);
        cout << "Total Giving Candy Count is "<< result << endl;
        cout << "--------------------------------------------" << endl << endl;
    }

	return 0;
}

