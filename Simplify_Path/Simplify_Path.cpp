// Simplify_Path.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        string  result;
        string  singleElem;
        vector<string>  stack;
        int n = path.size();
        if (n == 0)
            return "";

        int pos = 0, nextPos = 0;

        while (pos < n)
        {
            assert(path[pos] == '/');
            if (pos == n - 1)
                break;

            nextPos = getNextSlash(path, pos+1);
            singleElem = path.substr(pos+1, nextPos - pos - 1);

            if (singleElem == ".." && stack.size() > 0)
                stack.pop_back();
            else if (singleElem.size() > 0 && singleElem != ".")
                stack.push_back(singleElem);

            pos = nextPos;
        }

        result = "";
        for (int i = 0; i < stack.size(); i++)
        {
            result += "/";
            result += stack[i];
        }

        return result;
    }

private:
    inline int getNextSlash(const string& path, int start)
    {
        while (start < path.size())
        {
            if (path[start] == '/')
                break;
            start++;
        }
        return start;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    string  path = "////home//////";
    Solution so;
    string res = so.simplifyPath(path);
	return 0;
}

