// Longest_Valid_Parentheses.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if (n < 2)  return 0;

        stack<char> parenthesisStack;
        stack<int>     validCountStack;
        parenthesisStack.push('%');
        validCountStack.push(0);

        int curCount = 0; int maxCount = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                parenthesisStack.push(s[i]);
                validCountStack.push(0);
            }
            else if (s[i] == ')')
            {
                if (parenthesisStack.top() == '(')
                {
                    parenthesisStack.pop();
                    curCount = validCountStack.top() + 1;
                    validCountStack.pop();
                    assert(!validCountStack.empty());
                    validCountStack.top() += curCount;

                    if (validCountStack.top() > maxCount)
                        maxCount = validCountStack.top();
                }
                else
                {
                    parenthesisStack.push(s[i]);
                    validCountStack.push(0);
                }
            }
            else
                assert(0);
        }

        assert(!parenthesisStack.empty() && !validCountStack.empty());
        return maxCount*2;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string s = ")((()))())(())())(";
    Solution so;
    so.longestValidParentheses(s);

	return 0;
}

