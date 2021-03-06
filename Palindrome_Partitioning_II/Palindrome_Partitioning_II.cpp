// Palindrome_Partitioning_II.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************************
    Given a string s, partition s such that every substring of the partition is a palindrome.

    Return the minimum cuts needed for a palindrome partitioning of s.

    For example, given s = "aab",
    Return 1 since the palindrome partitioning["aa", "b"] could be produced using 1 cut.
********************************************************************************/

#include "stdafx.h"
#include <string>

using namespace std;


/*Dynamic Programming*/

class Solution {
public:
    int minCut(string str) {
        int size = str.size();

        if (size < 2)
            return 0;

        int     *minCutA = new int[size+1];
        int s, j;
        char  *tempBuffer = new char[size*size*sizeof(bool)  + size*sizeof(bool*)];
        bool**  isPalin = (bool**)(tempBuffer + size*size*sizeof(bool));
        //assign bool[] pointer and the bool pointer
        for (j = 0; j < size; j++)
        {
            isPalin[j] = (bool*)(tempBuffer + size*sizeof(bool)*j);
        }
        
        minCutA[size] = -1;

        int minCutV;
        bool isPalV;

        for (s = size - 1; s >= 0; s--)
        {
            minCutV = size - s - 1;

            for (j = s; j < size; j++)
            {
                isPalV = false;
                if (  str[j] == str[s] 
                       &&
                      (j - s < 2 || isPalin[s+1][j-1])
                 )
                {
                    isPalV = true;
                }

                isPalin[s][j] = isPalV;
                if (isPalV)
                {
                    if (1 + minCutA[j + 1] < minCutV)
                        minCutV = 1 + minCutA[j + 1];
                }
            }

            minCutA[s] = minCutV;
        }

        minCutV = minCutA[0];
        delete[] tempBuffer;
        delete[] minCutA;

        return minCutV;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

