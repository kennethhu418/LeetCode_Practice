// CommonClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyStack.h"


int _tmain(int argc, _TCHAR* argv[])
{
    MyStack<int> stack;

    stack.Push(3);
    stack.Peak() = 10;

    int a;
    stack.Pop(a);

    printf("%d\n", a);

	return 0;
}

