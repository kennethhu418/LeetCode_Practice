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
        vector<Interval>    result;
        int     n = array.size();
        if (n == 0)
        {
            result.push_back(newInterval);
            return result;
        }

        //find non-overlap intervals before the new Interval and directly put them into the result
        int     curPos;
        for (curPos = 0; curPos < n; curPos++)
        {
            if (array[curPos].end >= newInterval.start)
                break;
            result.push_back(array[curPos]);
        }

        if (curPos == n)
        {
            result.push_back(newInterval);
            return result;
        }

        //merge the newInterval with the overlapped intervals if there is any
        if (array[curPos].start > newInterval.end)
            result.push_back(newInterval);
        else
        {
            newInterval.start = (newInterval.start < array[curPos].start ? newInterval.start : array[curPos].start);
            newInterval.end = (newInterval.end >array[curPos].end ? newInterval.end : array[curPos].end);
            curPos++;

            while (curPos < n)
            {
                if (array[curPos].start > newInterval.end)
                    break;
                newInterval.end = (newInterval.end >array[curPos].end ? newInterval.end : array[curPos].end);
                curPos++;
            }

            result.push_back(newInterval);
        }

        //at last put all remaining non-overlap array intervals into the result
        while (curPos < n)
        {
            result.push_back(array[curPos]);
            curPos++;
        }

        return result;
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

