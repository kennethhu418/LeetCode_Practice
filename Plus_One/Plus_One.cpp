// Plus_One.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int n = digits.size();
        vector<int>     result;
        if (n == 0)
            return result;

        bool  carry_over = true;

        for (int i = n - 1; i >= 0; i--)
        {
            if (carry_over)
            {
                if (digits[i] == 9)
                    result.push_back(0);
                else
                {
                    result.push_back(digits[i] + 1);
                    carry_over = false;
                }
            }
            else
                result.push_back(digits[i]);
        }

        if (carry_over)
            result.push_back(1);

        ReverseVector(result);
        return result;
    }

private:
    inline void ReverseVector(vector<int> &array)
    {
        int     start = 0, end = array.size() - 1;
        while (start < end)
        {
            array[start] ^= array[end];
            array[end] ^= array[start];
            array[start] ^= array[end];
            start++;    end--;
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<int>     orgdata;
    orgdata.push_back(9);
    orgdata.push_back(9);
    orgdata.push_back(9);    

    Solution    s;
    vector<int> result = s.plusOne(orgdata);

	return 0;
}

