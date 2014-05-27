// Edit_Distance.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size();
        int n2 = word2.size();
        if (n1 == 0) return n2;
        if (n2 == 0) return n1;

        int** distArray = new int*[n1+1];
        for (int i = 0; i <= n1; i++)
            distArray[i] = new int[n2+1];

        distArray[n1][n2] = 0;
        for (int i = n2 - 1; i >= 0; i--)
            distArray[n1][i] = 1 + distArray[n1][i + 1];
        for (int i = n1 - 1; i >= 0; i--)
            distArray[i][n2] = 1 + distArray[i + 1][n2];

        int curDist = 0; int minDist = 0;

        for (int i = n1 - 1; i >= 0; i--)
        {
            for (int j = n2 - 1; j >= 0; j--)
            {
                if (word1[i] == word2[j])
                {
                    distArray[i][j] = distArray[i+1][j+1];
                    continue;
                }

                //replace dist
                minDist = 1 + distArray[i+1][j+1];
                //delete dist
                curDist = 1 + distArray[i + 1][j];
                if (curDist < minDist)
                    minDist = curDist;
                //insert dist
                curDist = 1 + distArray[i][j+1];
                if (curDist < minDist)
                    minDist = curDist;

                distArray[i][j] = minDist;
            }
        }

        minDist = distArray[0][0];
        for (int i = 0; i < n1; i++)
            delete[] distArray[i];
        delete[] distArray;

        return minDist;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

