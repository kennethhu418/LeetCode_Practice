// Word_Ladder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_set>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <assert.h>

using namespace std;

/****************************************************************************************************************
Given two words(start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that :

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given :
      start = "hit"
      end = "cog"
      dict = ["hot", "dot", "dog", "lot", "log"]
      As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
      return its length 5.

  Note :
       Return 0 if there is no such transformation sequence.
       All words have the same length.
       All words contain only lowercase alphabetic characters.
  ****************************************************************************************************************/


class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        if (start == end)
            return 1;

        queue<string>* curQueue = &curLevelQueue;
        queue<string>* nextQueue = &nextLevelQueue;
        queue<string>* tempQueue;
        int curQueueHeight = 1;
        bool transformedToEnd = false;

        curQueue->push(start);
        if (dict.find(start) != dict.end())
            dict.erase(start);

        while (!curQueue->empty())
        {
            while (!curQueue->empty())
            {
                start = curQueue->front();
                curQueue->pop();

                transformedToEnd = doTransformationAndMoveDictWordsToQueue(start, end, dict, *nextQueue);
                if (transformedToEnd)
                    return curQueueHeight + 1;
            }

            tempQueue = curQueue;
            curQueue = nextQueue;
            nextQueue = tempQueue;
            curQueueHeight++;
        }

        return 0;
    }

private:
    queue<string>  curLevelQueue;
    queue<string>  nextLevelQueue;

    //Transform the given string by replacing each character into another strings.
    //If one transformed string is in the given dictionary, remove it from the dictionary and put it into the given queue.
    //If one transformed string is the destination string, stop transformation and return true.
    bool doTransformationAndMoveDictWordsToQueue(const string& str, const string& destStr, unordered_set<string> &dict, queue<string> &wordsQueue)
    {
        string curStr = str;
        char orgChar;
        int n = str.size();

        if (curStr == destStr)
            return true;

        for (int curPos = 0; curPos < n; curPos++)
        {
            orgChar = curStr[curPos];

            for (char c = 'a'; c <= 'z'; c++)
            {
                curStr[curPos] = c;
                if (curStr == destStr)
                    return true;

                if (dict.find(curStr) == dict.end())
                    continue;

                wordsQueue.push(curStr);
                dict.erase(curStr);
            }

            curStr[curPos] = orgChar;
        }

        return false;
    }

    void RemoveWordsFromDict(unordered_set<string> &dict, queue<string> &wordsQueue)
    {
        int n = wordsQueue.size();
        while (n)
        {
            string word = wordsQueue.front();
            wordsQueue.pop();
            if (dict.find(word) != dict.end())
                dict.erase(word);
            wordsQueue.push(word);
            n--;
        }
        return;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    ifstream fin;
    unordered_set<string> dict;
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << q.size() << endl;

    fin.open("D:\\test.txt");
    string s;

    while (!fin.eof())
    {
        fin >> s;
        dict.insert(s);
    }
    fin.close();

    string start = "cet";
    string end = "ism";

    Solution solution;

    int retVal = solution.ladderLength(start, end, dict);
    cout << retVal << endl;

    system("PAUSE");
	return 0;
}

