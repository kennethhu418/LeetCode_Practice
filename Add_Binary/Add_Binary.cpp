// Add_Binary.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        int     sizea = a.size();
        int     sizeb = b.size();
        string result = "";

        if (sizea == 0) return b;
        if (sizeb == 0) return a;

        int     curA = sizea - 1, curB = sizeb - 1;
        bool carry_over = false;

        while (curA >= 0 && curB >= 0)
        {
            if (carry_over)
            {
                if (a[curA] == '0' && b[curB] == '0')
                {
                    result += '1';  carry_over = false;
                }
                else if (a[curA] == '0' || b[curB] == '0')
                    result += '0';
                else
                    result += '1';
            }
            else
            {
                if (a[curA] == '0' && b[curB] == '0')
                    result += '0';
                else if (a[curA] == '0' || b[curB] == '0')
                    result += '1';
                else
                {
                    result += '0';  carry_over = true;
                }
            }

            curA--; curB--;
        }

        if (curA >= 0)
            addRemainingPart(result, a, curA, carry_over);
        else if (curB >= 0)
            addRemainingPart(result, b, curB, carry_over);
        
        if (carry_over)
            result += '1';

        reverseString(result);
        return result;
    }

private:
    inline  void  addRemainingPart(string& dest, const string& str, int start, bool &carry_over)
    {
        while (start >= 0)
        {
            if (str[start] == '0')
            {
                if (carry_over)
                {
                    dest += '1';  carry_over = false;
                }
                else
                    dest += '0';
            }
            else
            {
                if (carry_over)
                    dest += '0';
                else
                    dest += '1';
            }

            start--;
        }
    }

    inline void reverseString(string& dest)
    {
        int start = 0, end = dest.size() - 1;
        char tmp;
        while (start < end)
        {
            tmp = dest[start];
            dest[start] = dest[end];
            dest[end] = tmp;
            start++;    end--;
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    string a = "1111";
    string b = "1011";

    Solution    so;
    string res = so.addBinary(a, b);

	return 0;
}

