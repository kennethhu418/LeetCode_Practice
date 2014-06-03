// Multiply_Strings.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <assert.h>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int size1 = num1.size();
        int size2 = num2.size();
        assert(size1 && size2);

        int singlePosNum = -1;
        string singlePosMulResult;
        string result = "0";

        for (int i = size2 - 1; i >= 0; i--)
        {
            singlePosNum = num2[i] - '0';
            multiplySinglePosWithPaddingZeros(num1, singlePosNum, singlePosMulResult, size2 - 1 - i);
            result = addStrings(result, singlePosMulResult);
        }

        int leadingZeroNum = getLeadingZeros(result);
        if (leadingZeroNum == result.size())
            return "0";
        else
            return result.substr(leadingZeroNum);
    }

private:
    inline int getLeadingZeros(const string& s)
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if (s[i] != '0')
                return i;
        }
        return n;
    }

    inline void reverseString(string& s)
    {
        int start = 0, end = s.size() - 1;
        char temp;
        while (start < end)
        {
            temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++; end--;
        }
    }

    inline void multiplySinglePosWithPaddingZeros(const string & num, int singleNum, string& result, int paddedZeroNum)
    {
        if (singleNum == 0)
        {
            result = "0";   return;
        }

        result.clear();
        for (int i = 0; i < paddedZeroNum; i++)
            result += '0';

        int carry_over = 0;
        int n = num.size();
        int curRes;
        for (int i = n - 1; i >= 0; i--)
        {
            curRes = carry_over + (num[i] - '0')*singleNum;
            carry_over = curRes / 10;
            result += ('0' + curRes - 10 * carry_over);
        }

        if (carry_over)
        {
            result += ('0' + carry_over);
        }

        reverseString(result);
    }

    inline string addStrings(const string& src1, const string& src2)
    {
        int m = src1.size() - 1, n = src2.size() - 1;
        int carry_over = 0, curRes;
        string result;

        while (m >= 0 && n >= 0)
        {
            curRes = (src1[m] - '0') + (src2[n] - '0') + carry_over;
            carry_over = curRes / 10;
            result += ('0' + curRes - 10*carry_over);
            m--; n--;
        }

        while (m >= 0)
        {
            curRes = (src1[m] - '0') + carry_over;
            carry_over = curRes / 10;
            result += ('0' + curRes - 10 * carry_over);
            m--;
        }

        while (n >= 0)
        {
            curRes = (src2[n] - '0') + carry_over;
            carry_over = curRes / 10;
            result += ('0' + curRes - 10 * carry_over);
            n--;
        }

        if (carry_over)
            result += ('0' + carry_over);

        reverseString(result);
        return result;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    string num1 = "98212";
    string num2 = "00";

    Solution so;
    string result = so.multiply(num1, num2);

	return 0;
}

