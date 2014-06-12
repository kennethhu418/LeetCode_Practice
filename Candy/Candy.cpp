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

class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        if (n == 0) return 0;
        if (n == 1) return 1;

        int total = 0, prevPersonCandyCount = 0;
        int high1 = -1, high2 = -1, low = -1, curPos = -1, high1CandyCount = 0;
        while (high1 < n)
        {
            low = getNextLow(ratings, high1 + 1);
            if (low >= n)
                break;

            high2 = getNextHigh(ratings, low + 1);

            total++;    prevPersonCandyCount = 1; //lowest rating person gets 1 candy
            curPos = low - 1;
            while (curPos >= 0 && curPos >= high1)
            {
                if (ratings[curPos] == ratings[curPos + 1])
                {
                    if (curPos != high1)
                    {
                        total++;    prevPersonCandyCount = 1;
                    }                    
                }
                else
                {
                    assert(ratings[curPos] > ratings[curPos + 1]);
                    prevPersonCandyCount++;

                    if (curPos == high1)
                    {
                        if (prevPersonCandyCount > high1CandyCount)
                        {
                            total -= high1CandyCount;
                            total += prevPersonCandyCount;
                        }
                    }
                    else
                        total += prevPersonCandyCount;                    
                }
                curPos--;
            }

            curPos = low + 1; prevPersonCandyCount = 1;
            while (curPos < n && curPos <= high2)
            {
                if (ratings[curPos] == ratings[curPos - 1])
                {
                    total++;    prevPersonCandyCount = 1;
                }
                else
                {
                    assert(ratings[curPos] > ratings[curPos - 1]);
                    total += (prevPersonCandyCount + 1);
                    prevPersonCandyCount++;
                }
                curPos++;
            }
            
            high1 = high2;
            high1CandyCount = prevPersonCandyCount;
        }

        return total;       
    }

private:
    inline int getNextHigh(vector<int> &ratings, int start)
    {
        int n = ratings.size();
        if (start >= n)
            return n;

        int left, right;

        while (start < n)
        {
            if (start == n - 1) return start;
            if (start == 0)
                left = MIN_INT;
            else
                left = ratings[start - 1];
            right = ratings[start + 1];

            if (ratings[start] >= left && ratings[start] > right)
                return start;

            start++;
        }

        return n;
    }

    inline int getNextLow(vector<int> &ratings, int start)
    {
        int n = ratings.size();
        if (start >= n)
            return n;

        int left, right;

        while (start < n)
        {
            if (start == n - 1) return start;
            if (start == 0)
                left = MAX_INT;
            else
                left = ratings[start - 1];
            right = ratings[start + 1];

            if (ratings[start] <= left && ratings[start] < right)
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

