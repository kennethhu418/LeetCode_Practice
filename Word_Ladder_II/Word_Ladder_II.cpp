// Word_Ladder_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_set>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

typedef struct __Elem
{
    string  str;
    vector<string>  curPathString;
}Elem;

class Solution {
public:
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        resultV.clear();

        if (start == end)
        {
            vector<string> v;
            v.push_back(start);
            resultV.push_back(v);
            return resultV;
        }

        queue<Elem>     exeQueue;
        Elem e;
        Elem newE;
        e.str = start;
        exeQueue.push(e);

        curMin = 0xFFFFFF;
        int     curDepth = 0;

        if (dict.find(start) != dict.end())
            dict.erase(start);
        

        while (!exeQueue.empty())
        {
            //poped out elem's string is definitely not equal to end and is not in dict now
            e = exeQueue.front();
            exeQueue.pop();
            start = e.str;
            e.curPathString.push_back(start);            

            curDepth = e.curPathString.size();
            if (curDepth  > curMin - 1)
                continue;

            bool cont = true;

            for (int s = 0; cont && s < start.size(); s++)
            {
                char orgChar = start[s];
                for (char a = 'a'; a <= 'z'; a++)
                {
                    if (a == orgChar)
                        continue;

                    start[s] = a;
                    if (start == end)
                    {
                        e.curPathString.push_back(start);
                        e.str = start;
                        InsertEndResult(e);
                        cont = false;
                        break;
                    }

                    if (dict.find(start) == dict.end())
                        continue;

                    e.str = start;
                    exeQueue.push(e);
                    dict.erase(start); 
                }

                start[s] = orgChar;
            }

        }

        return resultV;;


    }

private:
    vector<vector<string>>  resultV;
    int curMin;

    void InsertEndResult(Elem& e)
    {
        int curDepth = e.curPathString.size();
        if (curDepth > curMin)
            return;

        if (curDepth == curMin)
        {
            resultV.push_back(e.curPathString);
            return;
        }

        resultV.clear();
        resultV.push_back(e.curPathString);
        curMin = curDepth;
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

    string start = "hit";
    string end = "cog";

    Solution solution;
    vector<vector<string>>  resultV;

    resultV = solution.findLadders(start, end, dict);

    for (int i = 0; i < resultV.size(); i++)
    {
        for (int j = 0; j < resultV[i].size(); j++)
            cout << resultV[i][j] << " ";
        cout << endl;
    }
    
	return 0;
}

