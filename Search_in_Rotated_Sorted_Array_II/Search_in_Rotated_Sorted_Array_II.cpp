// Search_in_Rotated_Sorted_Array_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <queue>

using namespace std;

typedef struct __RangeElem
{
    int start;
    int end;
}RangeElem;

static int debug_complexity = 0;
static int debug_complexity2 = 0;

//We consider there are duplicates data in the array case. So this program is applicable for both
//Search_in_Rotated_Sorted_Array and Search_in_Rotated_Sorted_Array_II.
class Solution {
public:
    bool search(int A[], int n, int target) {
        if (n == 0) return false;

        if (n == 1)
        {
            if (A[0] == target) return true;
            return false;
        }

        ClearQueue();

        RangeElem   elem = { 0, n - 1 };
        int     start, end, mid;
        q.push(elem);

        while (!q.empty())
        {
            debug_complexity++;

            elem = q.front();
            q.pop();
            start = elem.start;
            end = elem.end;

            if (start > end)
                continue;

            if (start == end)
            {
                if (A[start] == target)
                    return true;
                continue;
            }

            if (A[start] == target) return true; //trim so that program can exit faster
            if (A[end] == target)   return true;  //trim so that program can exit faster

            mid = (start + end) / 2;
            if (target == A[mid])
                return true;

            if (A[start] == A[end] && A[start] == A[mid])
            {
                elem.start = start; elem.end = mid - 1; q.push(elem);
                elem.start = mid + 1; elem.end = end; q.push(elem);
                continue;
            }

            if (A[start] < A[end])
            {
                FindInStartLessThanEndCase(A, start, end, target);
                continue;
            }

            FindInStartGreaterEqualEndCase(A, start, end, target);
        }

        return false;
    }

private:
    queue<RangeElem>    q;

    inline void ClearQueue()
    {
        while (!q.empty())
            q.pop();
    }

    inline void FindInStartLessThanEndCase(int A[], int start, int end, int target)
    {
        int mid = (start + end) / 2;
        RangeElem   e;

        if (target < A[start] || target > A[end]) //trim so that program can exit faster
            return;

        if (target < A[mid])
        {
            e.start = start;
            e.end = mid - 1;
            q.push(e);
            return;
        }

        e.start = mid + 1;
        e.end = end;
        q.push(e);
    }

    inline void FindInStartGreaterEqualEndCase(int A[], int start, int end, int target)
    {
        int mid = (start + end) / 2;
        RangeElem   e;

        if (A[mid] >= A[start])
        {
            if (target < A[mid] && target < A[start])
            {
                if (target > A[end])    return;  //trim so that program can exit faster
                e.start = mid + 1;
                e.end = end;
                q.push(e);
                return;
            }

            if (target > A[mid])
            {
                e.start = mid + 1;
                e.end = end;
                q.push(e);
                return;
            }

            e.start = start;
            e.end = mid - 1;
            q.push(e);
            return;
        }

        if (target < A[mid])
        {
            e.start = start;
            e.end = mid - 1;
            q.push(e);
            return;
        }

        if (target > A[mid] && target < A[end])
        {
            e.start = mid + 1;
            e.end = end;
            q.push(e);
            return;
        }

        if (target < A[start]) //trim so that program can exit faster
            return;

        e.start = start;
        e.end = mid - 1;
        q.push(e);
        return;
    }
};


bool testFuncStandardAnswer(int A[], int n, int target, int& complexity)
{
    for (int i = 0; i < n; i++)
    {
        if (A[i] == target)
        {
            complexity = i + 1;
            return true;
        }            
    }

    complexity = n;
    return false;
}

//Answer from "水中的鱼"
class Solution_Others {
public:
    bool search(int A[], int n, int target) {
        int start = 0;
        int end = n - 1;

        while (start <= end)
        {
            int mid = (start + end) / 2;
            debug_complexity2++;

            if (A[mid] == target) 
                return true;

            if (A[start] < A[mid])
            {
                if (target >= A[start] && target<A[mid])
                    end = mid - 1;
                else
                    start = mid + 1;
            }
            else if (A[start] > A[mid])
            {
                if (target>A[mid] && target <= A[end])
                    start = mid + 1;
                else
                    end = mid - 1;
            }
            else //skip duplicate one, A[start] == A[mid]  
                start++;
        }
        return false;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 6, 7, 8, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
    int n = 52;
    int target = 7;
    int standard_complxity;

    Solution    so;
    Solution_Others so2;
    cout << "Enter target: ";
    cin >> target;
    while (target >= 0)
    {
        debug_complexity = 0;
        debug_complexity2 = 0;
        standard_complxity = 0;
        cout << "Your answer: " << so.search(A, n, target) << endl;
        cout << "Ohter's answer: " << so2.search(A, n, target) << endl;
        cout << "Standard answer: " << testFuncStandardAnswer(A, n, target, standard_complxity) << endl;
        cout << "Complexity: " << debug_complexity << " vs " << debug_complexity2<<" vs "<<standard_complxity << endl << endl;
        cout << "Enter target: ";
        cin >> target;
    }

    return 0;
}