// Evaluate_Reverse_Polish_Notation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>
//#include "MyStack.h"

using namespace std;

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
            delete [] arr;
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

private:
    T*  arr;
    int maxSize;
    int top;
};


class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        int n = tokens.size();
        int index = 0;
        MyStack<int> stack;
        int retVal;
        int op1,op2;

        for (index = 0; index < n; index++)
        {
            if (IsNumber(tokens.at(index), retVal))
            {
                stack.Push(retVal);
            }
            else
            {
                if (retVal == -1)
                {
                    printf("Wrong format: %s\n", tokens.at(index).c_str());
                    return -1;
                }

                assert(stack.Pop(op1));
                assert(stack.Pop(op2));

                switch (retVal)
                {
                case 0: //+
                    op2 += op1;
                    break;
                case 1: //-
                    op2 -= op1;
                    break;
                case 2: //*
                    op2 *= op1;
                    break;
                case 3: //'/'
                    op2 /= op1;
                    break;
                default:
                    assert(0);
                }

                stack.Push(op2);                
            }
        }

        assert(stack.Pop(op2));
        assert(stack.IsEmpty());

        return op2;
    }

private:
    //Determine whether the string represents a number.
    //If it is number, then return true and place the number in retVal
    //If it is a operator, then return false and place the operator in retVal
    //(+:0 -:1 *:2 /:3)
    //If it is something else, return false and place -1 in retVal.
    bool IsNumber(string&s, int& retVal)
    {
        if (s.size() == 0)
        {
            retVal = -1;
            return false;
        }

        retVal = -1;

        if (s.size() == 1 && s.at(0) == '+')
        {
            retVal = 0;
            return false;
        }
        if (s.size() == 1 && s.at(0) == '/')
        {
            retVal = 3;
            return false;
        }
        if (s.size() == 1 && s.at(0) == '-')
        {
            retVal = 1;
            return false;
        }
        if (s.size() == 1 && s.at(0) == '*')
        {
            retVal = 2;
            return false;
        }

        int n = s.size();
		bool negativeNumber = false;
		int start = 0;

		if(s.at(0) == '-')
		{
			negativeNumber = true;
			start = 1;
		}

        retVal = 0;
        if (s.at(start) > '9' || s.at(start) < '0')
        {
            retVal = -1;
            return false;
        }

        retVal = s.at(start) - '0';
        for (int i = start+1; i < n; i++)
        {
            if (s.at(i) > '9' || s.at(i) < '0')
            {
                retVal = -1;
                return false;
            }

            retVal = retVal*10 + s.at(i) - '0';
        }

		if(negativeNumber)
			retVal = 0-retVal;

        return true;
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<string> v;  //["2", "1", "+", "3", "*"]
    Solution s;
    v.push_back("2");
    v.push_back("1");
    v.push_back("+");
    v.push_back("3");
    v.push_back("*");
    
    int ret = s.evalRPN(v);
    printf("result: %d\n\n", ret);

    v.clear(); //["4", "13", "5", "/", "+"] 

    v.push_back("4");
    v.push_back("13");
    v.push_back("5");
    v.push_back("/");
    v.push_back("+");

    ret = s.evalRPN(v);
    printf("result: %d\n\n", ret);

    v.clear(); //["18"]

    v.push_back("18");

    ret = s.evalRPN(v);
    printf("result: %d\n\n", ret);

    system("PAUSE");
	return 0;
}

