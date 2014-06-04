// Small_Practice.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
    string str;

    while (getline(cin, str))
    {
        cout << str.size() << endl;
        cout << str << endl << endl;
    }

    system("PAUSE");
	return 0;
}

