// LeetCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        unsigned int n = s.size();
        if (n == 0)
            return;

        RemoveAdditionalSpaces(s);

        n = s.size();
        if (n == 0)
            return;

        unsigned int curPos = 0, nextSpace = 0;
        while (curPos < n)
        {
            nextSpace = getNextSpace(s, curPos);
            reverseString(s, curPos, nextSpace - 1);
            curPos = nextSpace + 1;
        }

        reverseString(s, 0, n - 1);
    }

private:
    inline void RemoveAdditionalSpaces(string &s)
    {
        unsigned int n = s.size();
        unsigned int nextPlacePos = 0, curPos = 0, curWordStart = 0, nextSpace = 0;

        //get the first word start
        curPos = getNextLetter(s, 0);
        if (curPos == n)
        {
            s.clear();
            return;
        }

        while (curPos < n)
        {
            nextSpace = getNextSpace(s, curPos);
            if (nextPlacePos == curPos)
                nextPlacePos += (nextSpace - curPos);
            else
            {
                while (curPos < nextSpace)
                    s[nextPlacePos++] = s[curPos++];
            }

            s[nextPlacePos++] = ' ';
            curPos = getNextLetter(s, nextSpace);
        }

        s.resize(nextPlacePos - 1);
    }

    inline unsigned int getNextLetter(const string &s, int curPos)
    {
        unsigned int n = s.size();
        while (curPos < n && s[curPos] == ' ')
            curPos++;
        return curPos;
    }

    inline unsigned int getNextSpace(const string &s, int curPos)
    {
        unsigned int n = s.size();
        while (curPos < n && s[curPos] != ' ')
            curPos++;
        return curPos;
    }

    inline void reverseString(string &s, int start, int end)
    {
        char tempC;
        while (start < end)
        {
            tempC = s[start];
            s[start] = s[end];
            s[end] = tempC;
            start++; end--;
        }
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string temp = " I am  a little      boy who   is in EMC     ";
    string expected = "EMC in is who boy little a am I";
    Solution solution;

    solution.reverseWords(temp);

    if(temp == expected)
        printf("Success!\n");

    printf("%s\n", temp.c_str());

    system("PAUSE");

    return 0;
}