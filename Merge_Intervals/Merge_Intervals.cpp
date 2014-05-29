// Merge_Intervals.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
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
    vector<Interval> merge(vector<Interval> &array) {
        int     n = array.size();
        if (n < 2)  return array;

        vector<Interval>    result;
        Interval    mergedInterval(1, -1);
        sort(array.begin(), array.end(), compare);

        for (int i = 0; i < n; i++)
        {
            if (mergedInterval.start > mergedInterval.end)
            {
                mergedInterval = array[i];
                continue;
            }

            if (array[i].start <= mergedInterval.end)
            {
                if (mergedInterval.end < array[i].end)
                    mergedInterval.end = array[i].end;
                continue;
            }

            result.push_back(mergedInterval);
            mergedInterval.start = 1; mergedInterval.end = -1; i--;
        }

        if (mergedInterval.start <= mergedInterval.end)
            result.push_back(mergedInterval);

        return result;
    }

private:
    static bool compare(const Interval& v1, const Interval& v2)
    {
        return v2.start > v1.start;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    vector<Interval>    array;
    array.push_back(Interval(40, 90));
    array.push_back(Interval(5, 8));
    array.push_back(Interval(100, 102));
    array.push_back(Interval(30, 41));
    array.push_back(Interval(400, 409));
    array.push_back(Interval(91, 99));
    array.push_back(Interval(10, 30));

    //array.push_back(Interval(1, 4));
    //array.push_back(Interval(1, 4));

    Solution so;
    vector<Interval>    result = so.merge(array);
    

	return 0;
}

