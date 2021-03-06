// Palindrome Partitioning.cpp : 定义控制台应用程序的入口点。
//

/****************************************************************************
    Given a string s, partition s such that every substring of the partition is a palindrome.

    Return all possible palindrome partitioning of s.

    For example, given s = "aab",
    Return

    [
        ["aa", "b"],
        ["a", "a", "b"]
    ]
****************************************************************************/

#include "stdafx.h"
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>>  v1;
        vector<vector<string>>  v2;
        vector<string>  curStrV;
        vector<string>  prevStrV;
        string  curStr, curChar;
        vector<vector<string>>  *prevResult = &v1;
        vector<vector<string>>  *curResult = &v2;

        int size = s.size();
        if (size == 0)
            return v1;
        if (size == 1)
        {
            curStrV.push_back(s);
            v1.push_back(curStrV);
            return v1;
        }

        //Push the last char into the prevResult first
        curStr = s.substr(size - 1);
        curStrV.push_back(curStr);
        prevResult->push_back(curStrV);

        for (int curIndex = size - 2; curIndex >= 0; curIndex--)
        {
            curChar = s.substr(curIndex, 1);

            int prevCombCount = prevResult->size();

            //First take the current char as a string and add it to all
            //prev results
            for (int i = 0; i < prevCombCount; i++)
            {
                prevStrV = prevResult->at(i);
                curStrV.clear();
                curStrV.push_back(curChar);
                AppendStringVector(curStrV, prevStrV, 0);
                curResult->push_back(curStrV);
            }

            //Now see whether we can combine with the prev results
            //to get new result.
            for (int i = 0; i < prevCombCount; i++)
            {
                prevStrV = prevResult->at(i);
                int prevStrCount = prevStrV.size();

                //If the first string in prev result is a char and it is the same with the curChar
                if (curChar == prevStrV.at(0))
                {
                    curStr = curChar;
                    curStr += curChar;

                    curStrV.clear();
                    curStrV.push_back(curStr);
                    AppendStringVector(curStrV, prevStrV, 1);
                    curResult->push_back(curStrV);
                }

                //Do not use else here. This is because the curChar maybe "f" and the prevStrV is ["f", "f"]


                if (prevStrCount > 1 && curChar == prevStrV.at(1))
                {
                    //If the second string in prev result is a char and it is the same with the curChar
                    //then curChar + first string of prev result (which is a palindrome) + second string of prev result
                    //can be combined as a new Palindrome.
                    curStr = curChar;
                    curStr += prevStrV.at(0);
                    curStr += curChar;

                    curStrV.clear();
                    curStrV.push_back(curStr);
                    AppendStringVector(curStrV, prevStrV, 2);
                    curResult->push_back(curStrV);
                }
            }

            prevResult->clear();

            vector<vector<string>>  *temp = prevResult;
            prevResult = curResult;
            curResult = temp;            
        }

        return *prevResult; 
    }

private:
    void AppendStringVector(vector<string> &destination, vector<string> &source, int fromWhere)
    {
        int n = source.size();
        if (fromWhere >= n)
        {
            return;
        }

        for (int i = fromWhere; i < n; i++)
        {
            destination.push_back(source.at(i));
        }

        return;
    }

};

void DisplayResult(vector<vector<string>> &result)
{
    int combNumber = result.size();

    for (int i = 0; i < combNumber; i++)
    {
        int stringCount = result.at(i).size();

        for (int j = 0; j < stringCount; j++)
        {
            printf("%s ", result.at(i).at(j).c_str());
        }

        printf("\n");
    }

    printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    Solution solution;
    string s = "fff";
    vector<vector<string>> result;

    result = solution.partition(s);
    DisplayResult(result);

    system("PAUSE");

	return 0;
}

