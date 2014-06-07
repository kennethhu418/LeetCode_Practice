// Valid_Parentheses.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
#include <string>
#include <assert.h>

using std::stack;
using std::string;

class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        if (n == 0) return true;
        if (n == 1) return false;

        stack<char> stackA;        
        for (int i = 0; i < n; i++)
        {
            switch (s[i])
            {
            case '(':
            case '[':
            case '{':
                stackA.push(s[i]);
                break;

            case ')':
                if (stackA.empty() || stackA.top() != '(')
                    return false;
                stackA.pop();
                break;
            case ']':
                if (stackA.empty() || stackA.top() != '[')
                    return false;
                stackA.pop();
                break;
            case '}':
                if (stackA.empty() || stackA.top() != '{')
                    return false;
                stackA.pop();
                break;

            default:
                assert(0);
            }
        }

        if (stackA.empty())
            return true;
        return false;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

