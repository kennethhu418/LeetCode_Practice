// Best_Time_to_Buy_and_Sell_Stock_III.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();

        if (n < 2)
            return 0;

        int singleTranMaxProfitStart, singleTranMaxProfitEnd, tempPos;
        int singleTranMaxProfit = 0, leftSingleTranMaxProfit = 0, rightSingleTranMaxProfit = 0, innerMaxDiff = 0;
        int outRangeMaxProfit = 0;

        singleTranMaxProfit = getMaxDiffMinBeforeMax(prices, 0, n - 1, singleTranMaxProfitStart, singleTranMaxProfitEnd);

        if (singleTranMaxProfitStart >= 2)
            leftSingleTranMaxProfit = getMaxDiffMinBeforeMax(prices, 0, singleTranMaxProfitStart - 1, tempPos, tempPos);

        if (n - singleTranMaxProfitEnd > 2)
            rightSingleTranMaxProfit = getMaxDiffMinBeforeMax(prices, singleTranMaxProfitEnd + 1, n - 1, tempPos, tempPos);

        if (singleTranMaxProfitEnd - singleTranMaxProfitStart > 2)
            innerMaxDiff = getMaxDiffMaxBeforeMin(prices, singleTranMaxProfitStart + 1, singleTranMaxProfitEnd - 1, tempPos, tempPos);


        outRangeMaxProfit = leftSingleTranMaxProfit > rightSingleTranMaxProfit ? leftSingleTranMaxProfit : rightSingleTranMaxProfit;

        if (outRangeMaxProfit > innerMaxDiff)
            return singleTranMaxProfit + outRangeMaxProfit;

        return singleTranMaxProfit + innerMaxDiff;
    }

private:
    int getMaxDiffMinBeforeMax(vector<int> &prices, int start, int end, int &maxDiffSmallValPos, int &maxDiffLargeValPos)
    {
        assert(start <= end);
        maxDiffSmallValPos = maxDiffLargeValPos = start;
        if (start == end)
        {
            return 0;
        }

        int maxPrice = 0 - 0x7FFFFFFF;
        int maxDiff = 0 - 0x7FFFFFFF;
        int maxPricePos = start;

        for (int s = end; s >= start; s--)
        {
            if (prices[s] > maxPrice)
            {
                maxPricePos = s;
                maxPrice = prices[s];
            }

            if (maxPrice - prices[s] > maxDiff)
            {
                maxDiffSmallValPos = s;
                maxDiffLargeValPos = maxPricePos;
                maxDiff = maxPrice - prices[s];
            }
        }

        return maxDiff;
    }

    int getMaxDiffMaxBeforeMin(vector<int> &prices, int start, int end, int &maxDiffSmallValPos, int &maxDiffLargeValPos)
    {
        assert(start <= end);
        maxDiffSmallValPos = maxDiffLargeValPos = start;
        if (start == end)
        {
            return 0;
        }

        int maxPrice = 0 - 0x7FFFFFFF;
        int maxDiff = 0 - 0x7FFFFFFF;
        int maxPricePos = start;

        for (int s = start; s <= end; s++)
        {
            if (prices[s] > maxPrice)
            {
                maxPricePos = s;
                maxPrice = prices[s];
            }

            if (maxPrice - prices[s] > maxDiff)
            {
                maxDiffSmallValPos = s;
                maxDiffLargeValPos = maxPricePos;
                maxDiff = maxPrice - prices[s];
            }
        }

        return maxDiff;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int priceArr[] = { 3, 4, 5, 6, 1, 0, 0, 3, 2, 8 };
    vector<int> prices;

    int size = sizeof(priceArr) / sizeof(int);
    for (int i = 0; i < size; i++)
        prices.push_back(priceArr[i]);

    Solution solution;
    printf("Max profit is: %d\n\n", solution.maxProfit(prices));

    system("PAUSE");
    return 0;
}

