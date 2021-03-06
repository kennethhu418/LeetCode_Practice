// Best_Time_to_Buy_and_Sell_Stock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int		n = prices.size();
        if (n < 2)
            return 0;

        int currentMaxPrice = 0 - 0x7FFFFFFF;
        int currentMaxProfit = 0 - 0x7FFFFFFF;
        int currentProfit = 0;

        for (int e = n - 1; e >= 0; e--)
        {
            if (prices[e] > currentMaxPrice)
                currentMaxPrice = prices[e];

            currentProfit = currentMaxPrice - prices[e];
            if (currentProfit > currentMaxProfit)
                currentMaxProfit = currentProfit;
        }

        return currentMaxProfit;
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

