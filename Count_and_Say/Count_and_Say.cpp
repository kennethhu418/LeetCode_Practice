// Count_and_Say.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if (n == 0) return "";

        string result = "1";
        n--;
        while (n > 0)
        {
            result = generateNextSayWord(result);
            n--;
        }

        return result;
    }

private:
    inline string generateNextSayWord(const string& curWord)
    {
        int curPos = 0;
        int n = curWord.size();
        int count = 0;
        string result;

        while (curPos < n)
        {
            count = getSameCount(curWord, curPos);
            result += generateString(count);
            result += curWord[curPos];
            curPos += count;
        }

        return result;
    }

    inline int getSameCount(const string& word, int start)
    {
        int n = word.size();
        if (start >= n)
            return 0;

        int count = 1;
        for (int i = start + 1; i < n; i++)
        {
            if (word[i] != word[start])
                break;
            count++;
        }

        return count;
    }

    inline string generateString(int n)
    {
        string result;
        int r, m;

        if (n == 0)
            return "0";

        while (n > 0)
        {
            m = n / 10;
            r = n - 10 * m;
            result += ('0' + r);
            n = m;
        }

        r = 0; m = result.size() - 1;
        char tmp;
        while (r < m)
        {
            tmp = result[r];
            result[r++] = result[m];
            result[m--] = tmp;
        }

        return result;
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    string result;
    int n;
    Solution so;

    while (cin >> n)
    {
        result = so.countAndSay(n);
        cout << result << endl << endl;
    }


	return 0;
}

