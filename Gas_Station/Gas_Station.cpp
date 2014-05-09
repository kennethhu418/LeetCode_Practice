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
    Solution(int size = 0)
    {
        this->mStationNum = size;
    }

    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        mStationNum = gas.size();

        assert(mStationNum == cost.size());
       
        if (mStationNum == 0)
            return -1;
        else if (mStationNum == 1)
            return 0;

        int     curStation = 0;     //which station we currently arrive at and filled with its gas
        int     start = 0;               //the start station we currently determines
        int     exeStation = 0;    //The very first start point we determines. We always start trying from station 0
        int     totalFillGas = gas.at(0); //Since currently we are at station 0, we should fill its gas
        int     totalCost = 0;

        while (true)
        {
            //Currently we are at station curStation and filled with its gas
            if (cost.at(curStation) <= totalFillGas - totalCost)  //If we can drive to curStation's next station
            {
                totalCost += cost.at(curStation);

                curStation = GetNext(curStation);
                if (curStation == start)
                    return start;

                totalFillGas += gas.at(curStation); //fill with curStation's gas.
                continue;
            }

            //try whether the start  should be the current start's previous station. If it's not, continue to try
            //the previous one until we get to the first start station we tried (exeStation).
            while (cost.at(curStation) > totalFillGas - totalCost)  
            {
                if (start == GetNext(curStation))
                {
                    //from start station we have already goes to the last station but cannot goes from the last
                    //station to the start. So there is no available station starting from which we can finish a full circle
                    return -1;
                }

                //try to add previous station on the current path
                start = GetPrev(start);

                totalFillGas += gas.at(start);
                totalCost += cost.at(start);
            }
        }

        return start;
    }

    int GetNext(int cur)
    {
        return (cur + 1) % mStationNum;
    }

    int GetPrev(int cur)
    {
        if (cur == 0)
            return mStationNum - 1;

        return cur - 1;
    }

private:
    int     mStationNum;
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