// Scramble_String.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        int     n = s1.size();
        assert(s2.size() == n);

        if (n == 0)
            return true;
        if (n == 1)
            return (s1 == s2);

        //resultArr[len][start_s1][start_s2] records whether s1.substr(start_s1, len+1) and s2.substr(start_s2, len+1)
        //is scramble string
        bool*** resultArr = createTripleMatrixWithZero(n+1, n, n);
        
        //first fill len = 1
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (s1[i] == s2[j])
                    resultArr[1][i][j] = true;
            }
        }

        for (int len = 2; len <= n; len++)
        {
            for (int i = 0; i <= n - len; i++)  //s1.substr(i, len)
            {
                for (int j = 0; j <= n - len; j++) //s2.substr(j, len)
                {
                    for (int k = 0; k < len - 1; k++)
                    {
                        if (resultArr[k + 1][i][j] && resultArr[len - k - 1][i + k + 1][j + k + 1]
                            || resultArr[k + 1][i][j + len - k - 1] && resultArr[len - k - 1][i + k + 1][j])
                        {
                            resultArr[len][i][j] = true;
                            break;
                        }                            
                    }
                }
            }
        }

        bool finalRes = resultArr[n][0][0];
        releaseTripleMatrix(resultArr, n+1, n, n);

        return finalRes;
    }

private:
    bool***   createTripleMatrixWithZero(int n1, int n2, int n3)
    {
        assert(n1 && n2 && n3);

        bool*** tripleMatrix = new bool**[n1];
        for (int i = 0; i < n1; i++)
        {
            bool ** doubleMatrix = new bool*[n2];
            tripleMatrix[i] = doubleMatrix;
            for (int j = 0; j < n2; j++)
            {
                doubleMatrix[j] = new bool[n3];
                memset(doubleMatrix[j], 0, n3*sizeof(bool));
            }                
        }

        return tripleMatrix;
    }

    void releaseTripleMatrix(bool*** tripleMatrix, int n1, int n2, int n3)
    {
        assert(n1 && n2 && n3 && tripleMatrix);

        for (int i = 0; i < n1; i++)
        {
            bool ** doubleMatrix = tripleMatrix[i];
            for (int j = 0; j < n2; j++)
                delete[] doubleMatrix[j];
            delete[] doubleMatrix;
        }

        delete[] tripleMatrix;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string s1 = "great";
    string s2 = "tgkae";

    Solution    so;
    so.isScramble(s1, s2);

	return 0;
}

