// Word_Ladder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_set>
#include <unordered_map>
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


/**********************Basic Ideas*******************************************************
Dynamic Programming

Given a string str. We allocate a hash table T to store the string we have already checked. The key is a string and the value is the
shortest transformation length of this string. We try the following:
(1) Assume the first char needs to be replaced first.
      Assign 'a' - 'z' to the first char each time. So the string becomes str' each time.
      - Check whether str' is in the dictionary. If not, continue assign next char.
      - Check whether str' is in T. If it is, and the T[str'] > 0, which means we have got answer for str'. Then the minimum length of
        current transformation is T[str'] + 1. Then use it to update the global min of str; If T[str'] <=  0. which means we are checking
        str' or have already checked it but still have not got answer, then continue next char.
        If str' is not in T, which means we have never checked str'. So continue to recursively call the same procedure for str'
(2) Assume the second char needs to be replaced first.
      Same procedure with (1).
(3) Try each char until the end.
***************************************************************************************/


#define DEFAULT_STACK_SIZE 30

template <class T>
class MyStack
{
public:
    MyStack(int size = DEFAULT_STACK_SIZE)
    {
        this->maxSize = size;
        arr = new T[size];
        top = 0;
    }

    ~MyStack()
    {
        if (arr)
        {
            delete[] arr;
        }
    }

    bool Push(T elem)
    {
        if (top == maxSize)
        {
            return false;
        }

        arr[top++] = elem;
        return true;
    }

    bool Pop(T& elem)
    {
        if (top == 0)
        {
            return false;
        }

        elem = arr[--top];
        return true;
    }

    bool IsEmpty()
    {
        return (top == 0);
    }

    bool IsFull()
    {
        return (top == maxSize);
    }

    T& Peak()
    {
        T e;
        if (IsEmpty())
        {
            return e;
        }

        return arr[top - 1];
    }

private:
    T*  arr;
    int maxSize;
    int top;
};

typedef struct __StackElem
{
    int         step;
    string   str;
    char     curChar;
    int         curPos;
    int         subLen;
    int         minLen;
    char     orgChar;
}StackElem;

typedef struct  __Res2
{
    vector<string>  strRes;
    string s;
}Res2;

class Solution {
public:

    int ladderLength(string start, string end, unordered_set<string> &dict) {
        unordered_map<string, bool> hist;
        return ladderLength_Recursive(start, end, dict, hist);
    }


    int ladderLength_Recursive(string start, string end, unordered_set<string> &dict, unordered_map<string, bool> &hist) {
        if (start == end)
        {
            return 1;
        }            

        if (hist.find(start) != hist.end())  //the string is on current path stack.
        {
            return 0;
        }

        hist[start] = true; //put the current string on the current path stack.
        int subLen = 0;
        int minLen = 0;
        //string orgs = start;

        //cout << start << endl;

        for (int s = 0; s < start.size(); s++)
        {
            char orgChar = start[s];

            for (char i = 'a'; i <= 'z'; i++)
            {
                if (orgChar == i)
                    continue;

                start[s] = i;

                if (start == end) //end may not be in the dictionary
                {
                    start[s] = orgChar;
                    hist.erase(start);
                    return 2;
                }

                if (dict.find(start) == dict.end())
                {
                    continue;
                }

                subLen = ladderLength_Recursive(start, end, dict, hist);  //step 1

                if (subLen > 0 && minLen == 0)
                {
                    minLen = 1 + subLen;
                }
                else if (subLen > 0 && 1 + subLen < minLen)
                {
                    minLen = 1 + subLen;
                }

            }

            start[s] = orgChar;
        }

        hist.erase(start);

        return minLen;
    }
};

class Solution2 {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict, Res2 &finalR) {
        queue<Res2> wq;
        queue<int> lq;
        Res2 r;
        r.s = start;
        r.strRes.push_back(start);

        wq.push(r);
        lq.push(1);

        while (!wq.empty()){
            r = wq.front();
            string word(r.s);
            wq.pop();

            int lev = lq.front();
            lq.pop();
            for (int i = 0; i < word.length(); i++){
                char temp = word[i];
                for (char c = 'a'; c <= 'z'; c++){
                    word[i] = c;
                    if (word == end){
                        r.s = word;
                        r.strRes.push_back(word);
                        finalR = r;
                        return lev + 1;
                    }

                    if (dict.find(word) != dict.end()){
                        Res2 newR;
                        newR = r;
                        newR.s = word;
                        newR.strRes.push_back(word);
                        wq.push(newR);
                        lq.push(lev + 1);
                        dict.erase(word);
                    }
                    word[i] = temp;
                }
            }
        }
        return 0;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    ifstream fin;
    unordered_set<string> dict;

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

    Solution2 solution2;
    Res2 finalRes;
    retVal = solution2.ladderLength(start, end, dict, finalRes);
    cout << retVal << endl;

    system("PAUSE");
	return 0;
}

