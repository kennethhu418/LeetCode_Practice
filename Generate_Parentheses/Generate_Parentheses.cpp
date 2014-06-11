// Generate_Parentheses.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string>  result;
        if (n == 0) return result;
        if (n == 1) { result.push_back("()"); return result; }

        vector<vector<string>>  resultArray(n + 1);

        resultArray[0].push_back("");
        resultArray[1].push_back("()");

        for (int count = 2; count <= n; count++)
        {
            for (int innerCnt = 0; innerCnt < count; innerCnt++)
            {
                composeResult(resultArray[count], resultArray[innerCnt],
                    resultArray[count - 1 - innerCnt]);
            }
        }

        return resultArray[n];
    }

private:
    inline void composeResult(vector<string>& result, const vector<string>& innerRes, 
        const vector<string> &outterRes)
    {
        int n = innerRes.size(), m = outterRes.size();
        string singleRes;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                singleRes = "("; singleRes += innerRes[i];
                singleRes += ")"; singleRes += outterRes[j];
                result.push_back(singleRes);
            }
        }
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<string>  result;
    Solution    so;
    int n;

    while (std::cin >> n)
    {
        result = so.generateParenthesis(n);
        for (vector<string>::const_iterator iter = result.begin();
            iter != result.end(); iter++)
        {
            std::cout << *iter << std::endl;
        }
        std::cout << std::endl;
    }

	return 0;
}

