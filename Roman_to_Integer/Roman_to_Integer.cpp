// Roman_to_Integer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <assert.h>
#include <iostream>

using std::string;

class Solution {
public:
    int romanToInt(string s) {
        int result = 0;
        int n = s.size();

        for (int i = 0; i < n; i++)
        {
            switch (s[i])
            {
            case 'M':
                result += 1000;
                break;
            case 'D':
                result += 500;
                break;
            case 'C':
                if (i + 1 < n && s[i + 1] == 'M')
                {
                    result += 900;  i++;
                }                    
                else if (i + 1 < n && s[i + 1] == 'D')
                {
                    result += 400;  i++;
                }
                else
                    result += 100;
                break;
            case 'L':
                result += 50;
                break;
            case 'X':
                if (i + 1 < n && s[i + 1] == 'C')
                {
                    result += 90;  i++;
                }
                else if (i + 1 < n && s[i + 1] == 'L')
                {
                    result += 40;  i++;
                }
                else
                    result += 10;
                break;
            case 'V':
                result += 5;
                break;
            case 'I': 
                if (i + 1 < n && s[i + 1] == 'X')
                {
                    result += 9;  i++;
                }
                else if (i + 1 < n && s[i + 1] == 'V')
                {
                    result += 4;  i++;
                }
                else
                    result += 1;
                break;
            default:
                assert(0);
            }
        }

        return result;        
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string romanNum = "MCMLIV";

    Solution s;

    while (std::cin >> romanNum)
    {
        std::cout << s.romanToInt(romanNum) << std::endl;
    }

	return 0;
}

