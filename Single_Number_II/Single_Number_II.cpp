// Single_Number_II.cpp : 定义控制台应用程序的入口点。
//

/*************************************************************************************************/
//Given an array of integers, every element appears three times except for one.Find that single one.
//
//Note:
//Your algorithm should have a linear runtime complexity.Could you implement it without using extra memory ?
/*************************************************************************************************/

#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>

class Solution {
public:
    int singleNumber(int A[], int n) {

        //Assume the count of "1" on the ith bit of all the given numbers A[] is ni1. If ni1%3 == 1,
        //the ith bit of ones is set to 1, which means "1" on the ith bit occurs only once because 
        //three "1"s will zero the overall count.
        int         ones = 0; 
        //Same with ones, but the ith bit of twos is set to 1 when ni1%3 == 2
        int         twos = 0;

        int         temp;

        //If ni1%3 == 0, then the ith bit of ones and twos are both 0.

        /*****************************************************************************************
            We should have the following state machine of bit transition for a specific bit:

            ones:               0   0   1   0   0   1
            twos:               0   1   0   0   1   0
            current bit:    0   0   0   1   1   1
            ----------(after state transition)----------
            ones':              0   0   1   1   0   0
            twos':              0   1   0   0   0   1

            According to truth table to logic expression translation rule, we have following state transit expression:
            ones' = ones&(~twos)&(~current_bit) | (~ones)&(~twos)&current_bit
            twos' = (~ones)&twos&(~current_bit) | ones&(~twos)&current_bit
            *****************************************************************************************/

        for (int i = 0; i < n; i++)
        {
            temp = ones; //since ones will be mofified first and we need the original value of ones to calculate twos, save it here.
            ones = (ones&(~twos)&(~A[i])) | ((~ones)&(~twos)&A[i]);
            twos = ((~temp)&twos&(~A[i])) | (temp&(~twos)&A[i]);
        }

        //Since all numbers except the single number appears triple times, the "1"s on each bit cancel each other
        //when do accounting above. The only number that contributes to the accounting above is the single number.
        //If the single number appears once, it is left in ones; If it appears twice, it is left in twos.

        if (ones == 0)
            return twos; //the single number could be 0, so the returned twos is zero.

        assert(twos == 0);
        return ones;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int arr1[] = {1,1,1,2,2,2,3,3,3,4,8,5,6,4,5,6,4,5,6};
    int arr2[] = { 8, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 8, 5, 6, 4, 5, 6, 4, 5, 6 };
    int arr3[] = { 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 0, 5, 6, 4, 5, 6, 4, 5, 6 };
    int arr4[] = { 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 5, 6, 4, 5, 6, 4, 5, 6 };

    Solution s;
    printf("%d\n\n", s.singleNumber(arr1, sizeof(arr1)/sizeof(int)));
    printf("%d\n\n", s.singleNumber(arr2, sizeof(arr2) / sizeof(int)));
    printf("%d\n\n", s.singleNumber(arr3, sizeof(arr3) / sizeof(int)));
    printf("%d\n\n", s.singleNumber(arr4, sizeof(arr4) / sizeof(int)));

    system("PAUSE");
	return 0;
}

