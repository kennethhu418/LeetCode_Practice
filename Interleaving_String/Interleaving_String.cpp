// Interleaving_String.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int     m   =   s1.size();
        int     n    =  s2.size();
        int     t = s3.size();

        if (m + n != t)
            return false;

        if (m == 0)
            return s2 == s3;

        if (n == 0)
            return s1 == s3;

        m++;    n++;
        bool** resultA = new bool*[m];
        for (int i = 0; i < m; i++)
            resultA[i] = new bool[n];
        //char* buffer = new char[m*n*sizeof(bool) + m*sizeof(bool*)];
        //memset(buffer, 0, m*n*sizeof(bool)+m*sizeof(bool*));

        //bool    **resultA = (bool**)(buffer + m*n*sizeof(bool));        
        //for (int i = 0; i < m; i++)
        //    resultA[i] = (bool*)(resultA + i*n*sizeof(bool));

        m--;    n--;
        resultA[m][n] = true;

        for (int i = n - 1; i >= 0; i--)
        {
            if (s2[i] == s3[t - n + i])
                resultA[m][i] = resultA[m][i + 1];
            else
                resultA[m][i] = false;
        }

        for (int i = m - 1; i >= 0; i--)
        {
            if (s1[i] == s3[t - m + i])
                resultA[i][n] = resultA[i+1][n];
            else
                resultA[i][n] = false;
        }

        for (int i = m - 1; i >= 0; i--)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                if (s1[i] == s3[i + j])
                    resultA[i][j] = resultA[i + 1][j];
                else if (s2[j] == s3[i + j])
                    resultA[i][j] = resultA[i][j + 1];
                else
                    resultA[i][j] = false;
            }
        }

        bool finalRes = resultA[0][0];
        m++; n++;
        for (int i = 0; i < m; i++)
            delete[] resultA[i];
        delete[] resultA;

        return finalRes;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string s1 = "a";
    string s2 = "b";
    string s3 = "ab";

    char*  aaaaa = new char[4];
    delete[] aaaaa;

    Solution    s;
    s.isInterleave(s1, s2, s3);

	return 0;
}

