// Best_Time_to_Buy_and_Sell_Stock_II.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        if (n < 2)
            return 0;

        int totalProfit = 0;
        int curMinPriceIndex, curMaxPriceIndex;

        curMinPriceIndex = GetLocalMinIndex(prices, 0, n - 1);

        while (curMinPriceIndex < n - 1)
        {
            curMaxPriceIndex = GetLocalMaxIndex(prices, curMinPriceIndex + 1, n - 1);
            assert(prices[curMinPriceIndex] < prices[curMaxPriceIndex]);
            totalProfit += (prices[curMaxPriceIndex] - prices[curMinPriceIndex]);

            if (curMaxPriceIndex == n - 1)
                break;

            curMinPriceIndex = GetLocalMinIndex(prices, curMaxPriceIndex + 1, n - 1);
        }

        return totalProfit;
    }

private:
    int GetLocalMinIndex(vector<int> &prices, int start, int end)
    {
        assert(start <= end);
        if (start == end)
            return start;

        int cur = start;
        while (cur < end && prices[cur] >= prices[cur + 1])
            cur++;
        return cur;
    }

    int GetLocalMaxIndex(vector<int> &prices, int start, int end)
    {
        assert(start <= end);
        if (start == end)
            return start;

        int cur = start;
        while (cur < end && prices[cur] <= prices[cur + 1])
            cur++;
        return cur;
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

