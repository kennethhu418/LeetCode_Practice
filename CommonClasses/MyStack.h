#include "stdafx.h"

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

    T& Peak()
    {
        T e;
        if (IsEmpty())
        {
            return e;
        }

        return arr[top-1];
    }

private:
    T*  arr;
    int maxSize;
    int top;
};