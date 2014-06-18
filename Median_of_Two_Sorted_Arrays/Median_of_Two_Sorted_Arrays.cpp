// Median_of_Two_Sorted_Arrays.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <time.h> 
#include <algorithm>

class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int t = m + n;
        if (t == 0)
            return 0;

        if (t & 0x1)
        {
            return findKthElemInSortedArray(A, B, m, n, (t + 1) / 2);
        }

        int mid1 = findKthElemInSortedArray(A, B, m, n, t/2);
        int mid2 = findKthElemInSortedArray(A, B, m, n, t / 2 + 1);

        return ((double)mid1 + mid2) / 2;
    }

private:
    int     findKthElemInSortedArray(int A[], int B[], int m, int n, int k)
    {
        if (m == 0) return B[k - 1];
        if (n == 0) return A[k - 1];

        int startA = 0, startB = 0, endA = m - 1, endB = n - 1;
        int midA = 0, insertB = 0;
        int leftASize = 0, leftBSize = 0;

        while (startA <= endA && startB <= endB)
        {
            midA = (startA + endA) / 2;
            insertB = findInsertPos(B + startB, endB - startB + 1, A[midA]);
            insertB += startB;

            leftASize = midA - startA + 1;
            leftBSize = insertB - startB;

            if (insertB == 0)
            {
                if (k <= leftASize)
                    return A[startA + k - 1];
                startA = midA + 1;
                k -= leftASize;
                continue;
            }

            if (k == leftASize + leftBSize)
                return A[midA];

            if (k < leftASize + leftBSize)
            {
                endA = midA - 1;
                endB = insertB - 1;
                continue;
            }

            startA = midA + 1;
            startB = insertB;
            k -= (leftASize + leftBSize);            
        }

        if (startA > endA)
            return B[startB + k - 1];
        
        if (startB > endB)
            return A[startA + k - 1];

        assert(0);
        return -1;
    }

    inline int findInsertPos(int arr[], int n, int target)
    {
        int start = 0, end = n - 1, mid = -1;

        if (target < arr[0])
            return 0;
        if (target >= arr[end])
            return n;

        while (start < end)
        {
            mid = (start + end) / 2;

            if (target >= arr[mid])
            {
                start = mid + 1;
                continue;
            }

            end = mid - 1;
            continue;
        }

        if (start > end)
            return start;

        if (target >= arr[start])
            return start + 1;
        return start;
    }
};

void SplitArray(int T[], int t, int A[], int B[], int &m, int& n)
{
    m = rand() % (t + 1);
    n = t - m;

    unsigned int* posArray = new unsigned int[t];
    for (int i = 0; i < t; i++)
        posArray[i] = i;

    int pos = 0;
    for (int i = 0; i < m; i++)
    {
        pos = rand() % (t - i);
        std::swap(posArray[pos], posArray[t - i - 1]);
    }

    if (n > 0)
        std::sort(posArray, posArray + n);
    if (m > 0)
        std::sort(posArray + n, posArray + t);

    for (int i = 0; i < m; i++)
        A[i] = T[posArray[n + i]];
    for (int i = 0; i < n; i++)
        B[i] = T[posArray[i]];
}

void OutputTwoArrays(int A[], int m, int B[], int n)
{
    std::cout << "A: {";
    for (int i = 0; i < m; i++)
        std::cout << A[i] << " ";
    std::cout << "}" << std::endl;
    std::cout << "B: {";
    for (int i = 0; i < n; i++)
        std::cout << B[i] << " ";
    std::cout << "}" << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    int T[] = {1, 4, 7, 10, 13, 18, 19, 23, 28, 30};

    int A[20];
    int B[20];
    int m = -1, n = -1;
    char temp[30];
    Solution so;

    using namespace std;

    int a = 0x80000000, b = 0x80000000;
    cout << a / b << endl;

    srand(time(0));

    cout << "Usage:\nEnter \"R\" to use last generated arrays. Enter other strings to generate new arrays." << endl<<endl;

    while (cin >> temp)
    {
        if (*temp != 'R' && *temp != 'r' || m == -1)
        {
            SplitArray(T, sizeof(T) / sizeof(int), A, B, m, n);
            cout << "Generate New Arrays A and B." << endl;
        }
        else
            cout << "Use Last Generated Arrays A and B." << endl;            

        OutputTwoArrays(A, m, B, n);
        cout << "Median: "<<so.findMedianSortedArrays(A, m, B, n) << endl;
        cout << "----------------------------------------------------------------------------" << endl<<endl;
    }

	return 0;
}

