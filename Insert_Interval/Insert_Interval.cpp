// Insert_Interval.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;

typedef struct __Interval {
    int start;
    int end;
    __Interval() : start(0), end(0) {}
    __Interval(int s, int e) : start(s), end(e) {}
}Interval;

class Solution {
public:
    vector<Interval> insert(vector<Interval> &array, Interval newInterval) {
        int n = array.size();
        result.clear();

        if (n == 0)
        {
            result.push_back(newInterval);
            return result;
        }

        int extendedStart, extendedEnd;
        int endFindStart = 0, i;

        for (i = 0; i < n; i++)
        {
            if (newInterval.start > array[i].end)
                continue;

            if (newInterval.start < array[i].start)
            {
                extendedStart = newInterval.start;
                break;
            }

            extendedStart = array[i].start;
            break;
        }

        if (i == n)
        {
            result = array;
            result.push_back(newInterval);
            return result;
        }

        for (; i < n; i++)
        {
            if (newInterval.end > array[i].end)
                continue;
            if (newInterval.end < array[i].start)
            {
                extendedEnd = newInterval.end;
                break;
            }
            extendedEnd = array[i].end;
            break;
        }
        if (i == n)
            extendedEnd = newInterval.end;

        newInterval.start = extendedStart;
        newInterval.end = extendedEnd;

        excludeIntervals(array, newInterval);
        return result;
    }

private:
    vector<Interval> result;

    void excludeIntervals(vector<Interval> &array, Interval& targetInterval)
    {
        int i;
        for (i = 0; i < array.size(); i++)
        {
            if (array[i].end < targetInterval.start)
            {
                result.push_back(array[i]);
                continue;
            }

            break;
        }

        result.push_back(targetInterval);

        for (; i < array.size(); i++)
        {
            if (array[i].start <= targetInterval.end)
                continue;
            result.push_back(array[i]);
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<Interval>    array;
    array.push_back(Interval(1, 5));
    
    Solution    so;
    so.insert(array, Interval(2,3));

	return 0;
}

