// Word_Ladder_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_set>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

typedef struct __Elem
{
    string  str;
    vector<string>  curPathString;
}Elem;

class Solution_With_Queue {
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
        queue<Elem>     exeQueue_nextLevel;
        Elem e;
        Elem newE;
        e.str = start;
        exeQueue.push(e);
        if (dict.find(start) != dict.end())
            dict.erase(start);

        curMin = 0xFFFFFF;
        int     curDepth = 0;        

        while (!exeQueue.empty() || !exeQueue_nextLevel.empty())
        {
            if (exeQueue.empty())
            {
                while (!exeQueue_nextLevel.empty())
                {
                    dict.erase(exeQueue_nextLevel.front().str);
                    exeQueue.push(exeQueue_nextLevel.front());
                    exeQueue_nextLevel.pop();
                }
            }

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
                    exeQueue_nextLevel.push(e);
                }

                start[s] = orgChar;
            }

        }

        return resultV;
    }

private:
    vector<vector<string>>  resultV;
    int curMin;

    inline void InsertEndResult(Elem& e)
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


class Solution_Replace_Queue_With_Map {
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

        vector<string>     exeQueue;
        vector<string>     exeQueue_nextLevel;
        vector<string>*   curQueue = &exeQueue;
        vector<string>*   nextQueue = &exeQueue_nextLevel;

        if (dict.find(start) != dict.end())
            dict.erase(start);

        curQueue->push_back(start);
        pathMap[start].push_back(start);

        while (!curQueue->empty() || !nextQueue->empty())
        {
            if (curQueue->empty())
            {
                vector<string>::const_iterator itr = nextQueue->begin();
                for (; itr != nextQueue->end(); itr++)
                {
                    dict.erase(*itr);
                }

                vector<string>*   tempswap = curQueue;
                curQueue = nextQueue;
                nextQueue = tempswap;
                nextQueue->clear();
            }

            //poped out elem's string is definitely not equal to end and is not in dict now
            vector<string>::iterator itr = curQueue->begin();
            for(; itr != curQueue->end(); itr++)
            {
                start = *itr;

                bool cont = true;

                //Current level string has been put into the map and has no duplicates
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
                            pathMap[*itr].push_back(start);
                            OutputResult(pathMap[*itr]);
                            cont = false;
                            break;
                        }

                        if (dict.find(start) == dict.end())
                            continue;

                        if (pathMap.find(start) == pathMap.end())
                        {
                            pathMap[start] = pathMap[*itr];
                            pathMap[start].push_back(start);
                            nextQueue->push_back(start);
                        }
                    }
                    start[s] = orgChar;
                }
            }

        }

        return resultV;
    }

private:
    unordered_map<string, vector<string>>  pathMap;
    vector<vector<string>> resultV;
    int curMin;

    inline void OutputResult(vector<string>& curRes)
    {
        resultV.push_back(curRes);
    }

};


class Solution2 {
public:
    unordered_map<string, vector<string> > mp; // result map 
    vector<vector<string> > res;
    vector<string> path;

    void findDict2(string str, unordered_set<string> &dict, unordered_set<string> &next_lev){
        int sz = str.size();
        string s = str;
        for (int i = 0; i<sz; i++){
            s = str;
            for (char j = 'a'; j <= 'z'; j++){
                s[i] = j;
                if (dict.find(s) != dict.end()){
                    next_lev.insert(s);
                    mp[s].push_back(str);
                }
            }
        }
    }

    void output(string &start, string last){
        if (last == start){
            reverse(path.begin(), path.end());
            res.push_back(path);
            reverse(path.begin(), path.end());
        }
        else{
            for (int i = 0; i<mp[last].size(); i++){
                path.push_back(mp[last][i]);
                output(start, mp[last][i]);
                path.pop_back();
            }
        }
    }

    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        mp.clear();
        res.clear();
        path.clear();

        dict.insert(start);
        dict.insert(end);

        unordered_set<string> cur_lev;
        cur_lev.insert(start);
        unordered_set<string> next_lev;
        path.push_back(end);


        while (true){
            for (auto it = cur_lev.begin(); it != cur_lev.end(); it++){ dict.erase(*it); } //delete previous level words 

            for (auto it = cur_lev.begin(); it != cur_lev.end(); it++){  //find current level words 
                findDict2(*it, dict, next_lev);
            }

            if (next_lev.empty()){ return res; }

            if (next_lev.find(end) != next_lev.end()){ //if find end string 
                output(start, end);
                return res;
            }

            cur_lev.clear();
            cur_lev = next_lev;
            next_lev.clear();
        }
        return res;
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

    string start = "nape";
    string end = "mild";

    Solution_Replace_Queue_With_Map  solution;
    Solution2 solution2;
    vector<vector<string>>  resultV;

    resultV = solution.findLadders(start, end, dict);

    for (int i = 0; i < resultV.size(); i++)
    {
        for (int j = 0; j < resultV[i].size(); j++)
            cout << resultV[i][j] << " ";
        cout << endl;
    }

    fin.open("D:\\test.txt");
    dict.clear();
    while (!fin.eof())
    {
        fin >> s;
        dict.insert(s);
    }
    fin.close();

    cout << endl << endl;

    resultV = solution2.findLadders(start, end, dict);
    for (int i = 0; i < resultV.size(); i++)
    {
        for (int j = 0; j < resultV[i].size(); j++)
            cout << resultV[i][j] << " ";
        cout << endl;
    }

    
	return 0;
}

