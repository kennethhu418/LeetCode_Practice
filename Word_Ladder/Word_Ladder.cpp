// Word_Ladder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>

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

class Solution {
public:

    int ladderLength(string start, string end, unordered_set<string> &dict) {
        unordered_map<string, int> hist;
        return ladderLength_Recursive(start, end, dict, hist);
    }


    int ladderLength_Recursive(string start, string end, unordered_set<string> &dict, unordered_map<string, int> &hist) {
        if (start == end)
            return 1;
        if (start.size() != end.size())
            return -1;

        if (hist.find(start) != hist.end())
        {
            return hist[start];
        }

        hist[start] = -1;
        int subLen = 0;
        int minLen = -1;

        for (int s = 0; s < start.size(); s++)
        {
            char orgChar = start[s];

            for (char i = 'a'; i <= 'z'; i++)
            {
                if (orgChar == i)
                    continue;

                start[s] = i;
                if (dict.find(start) == dict.end() && start != end) //end may not be in the dictionary
                {
                    continue;
                }

                subLen = ladderLength_Recursive(start, end, dict, hist);  //step 1
                if (subLen > 0 && minLen == -1)
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

        hist[start] = minLen;

        return minLen;
    }

    int ladderLength_NonRecursive(string start, string end, unordered_set<string> &dict, unordered_map<string, int> &hist) {
        if (start == end)
            return 1;

        if (start.size()!= end.size())
            return -1;

        MyStack<StackElem>  stack;
        StackElem e = { 0, start, 'a', 0 , -1, 0x7FFFFFFF};
        stack.Push(e);

        while (!stack.IsEmpty())
        {
            StackElem &top = stack.Peak();
            start = top.str;

            if (top.step == 0)
            {
                if (start == end)
                {
                    stack.Pop(e);
                    if (!stack.IsEmpty())
                    {
                        stack.Peak().subLen = 1;
                    }
                    continue;
                }

                if (hist.find(start) != hist.end())
                {
                    stack.Pop(e);
                    if (!stack.IsEmpty())
                    {
                        stack.Peak().subLen = hist[start];                        
                    }
                    continue;
                }

                bool cont = true;
                top.minLen = -1;

                for (int s = 0; cont && s < start.size(); s++)
                {
                    char orgChar = start[s];

                    for (char i = 'a'; i <= 'z'; i++)
                    {
                        if (orgChar == i)
                            continue;

                        start[s] = i;
                        if (dict.find(start) == dict.end())
                        {
                            continue;
                        }

                        top.step = 1;
                        top.curChar = i;
                        top.curPos = s;
                        top.subLen = -1;

                        e.step = 0;
                        e.str = start;
                        stack.Push(e);
                        
                        cont = false;
                        break;
                    }

                    start[s] = orgChar;
                }

                stack.Pop(e);

                continue;
            }

            if (top.step == 1)
            {
                int s = top.curPos;
                char i = top.curChar;
                bool cont = true;

                if (top.subLen > 0 && top.minLen == -1)
                {
                    top.minLen = 1 + top.subLen;
                }
                else if (top.subLen > 0 && 1 + top.subLen < top.minLen)
                {
                    top.minLen = 1 + top.subLen;
                }

                i = top.curChar + 1;

                for (; cont && s < start.size(); s++)
                {
                    char orgChar = start[s];

                    for (; i <= 'z'; i++)
                    {
                        if (orgChar == i)
                            continue;

                        start[s] = i;
                        if (dict.find(start) == dict.end() && start != end)
                        {
                            continue;
                        }

                        top.step = 1;
                        top.curChar = i;
                        top.curPos = s;
                        top.subLen = -1;

                        e.step = 0;
                        e.str = start;
                        stack.Push(e);

                        cont = false;
                        break;
                    }

                    start[s] = orgChar;
                }

                stack.Pop(e);
            }            
        }

        return e.minLen;
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    Solution solution;
    string start = "hot";
    string end = "dog";
    std::unordered_set<string> dict;
    dict.insert("hot");
    dict.insert("dog");

    int retVal = solution.ladderLength(start, end, dict);
    cout << retVal << endl;

    system("PAUSE");
	return 0;
}

