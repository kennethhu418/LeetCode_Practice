// Restore_IP_Addresses.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;


//IP addresses only have 4 segments. We can use the recursive implementation because recursive implemention
//would only have 4 levels of recursion, which is a constant space complexity. So we can take the recursive
//implemention to deduce the code scale.

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        return restoreIPAddresses(s, 0, 4);
    }

private:
    vector<string> restoreIPAddresses(const string& s, int start, int segNum)
    {
        vector<string>  result;

        if (segNum == 0)
            return result;

        int size = s.size();

        if (size - start < segNum)
            return result;

        if (segNum == 1)
        {
            if (s[start] == '0')
            {
                if (size - start == 1)
                    result.push_back("0");
                return result;
            }

            if (size - start > 3)
                return result;

            int num = 0;
            for (int i = 0; i < size - start; i++)
                num = 10 * num + s[start + i] - '0';

            if (num < 256)
                result.push_back(s.substr(start));

            return result;
        }

        if (s[start] == '0')
        {
            vector<string>  subResult = restoreIPAddresses(s, start + 1, segNum - 1);
            CombineResults(result, "0", subResult);
        }
        else
        {
            int num = 0;
            for (int i = 1; i < 4; i++)
            {
                num = num * 10 + s[start + i - 1] - '0';
                if (num > 255)
                    break;

                vector<string>  subResult = restoreIPAddresses(s, start + i, segNum - 1);
                CombineResults(result, s.substr(start, i), subResult);
            }
        }

        return result;
    }

private:
    inline void CombineResults(vector<string>& result, const string& preNum, vector<string>& subResult)
    {
        int size = subResult.size();
        for (int i = 0; i < size; i++)
        {
            string s = preNum;
            s += ".";
            s += subResult.at(i);
            result.push_back(s);
        }
    }

};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

