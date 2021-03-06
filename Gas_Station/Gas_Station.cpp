// Gas_Station.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>
#include <stdlib.h>

/****************************************************************************************************************
    There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

    You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station(i + 1).You begin
    the journey with an empty tank at one of the gas stations.

    Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

    Note:
    The solution is guaranteed to be unique.
****************************************************************************************************************/

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int n = gas.size();
        assert(cost.size() == n);

        if (n == 1)
        {
            if (gas[0] >= cost[0])
                return 0;
            return -1;
        }

        int srcStation = 0, destStation = 1, curArrivedStation = 0, totalGas = gas[0];

        do
        {
            //Let's travel from curStation until blocked
            while (true)
            {
                if (totalGas >= cost[curArrivedStation])
                {
                    totalGas -= cost[curArrivedStation];
                    curArrivedStation = destStation;
                    totalGas += gas[curArrivedStation];
                    destStation = (curArrivedStation + 1) % n;
                    if (curArrivedStation == srcStation)
                        return srcStation;
                }
                else
                    break;
            }

            srcStation = (srcStation + n - 1) % n;
            while (srcStation != curArrivedStation)
            {
                totalGas += gas[srcStation];
                totalGas -= cost[srcStation];
                if (totalGas >= 0)
                    break;
                srcStation = (srcStation + n - 1) % n;
            }

            if (srcStation == curArrivedStation)
                return -1;
        } while (true);

        return -1;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> gas;
    gas.push_back(10);
    gas.push_back(20);

    vector<int> cost;
    cost.push_back(20);
    cost.push_back(15);

    Solution s;
    printf("%d\n\n", s.canCompleteCircuit(gas, cost));

    system("pause");
	return 0;
}