// Text_Justification.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string>  result;
        string  curLine = "";
        int n = words.size();
        if (n == 0)
        {
            for (int i = 0; i < L; i++)
                curLine += " ";
            result.push_back(curLine);
            return result;
        }
        if (n == 1) 
        { 
            curLine = words[0];
            for (int i = 0; i < L - words[0].size(); i++)
                curLine += " ";
            result.push_back(curLine); 
            return result;
        }

        int curStartPos = 0, curEndPos = 0;
        int curCharLen = 0, curWordNum = 0, curWordCharLen = 0;
        int spaceNum = 0, avgSpaceNum = 0, residuleSpaceNum = 0;

        while (curStartPos < n)
        {
            assert(words[curStartPos].size() <= L);
            curCharLen = words[curStartPos].size();
            curWordNum = 1; curWordCharLen = curCharLen;

            curEndPos = curStartPos + 1;
            while (curEndPos < n)
            {
                //space
                curCharLen++;
                if (curCharLen >= L)
                {
                    curEndPos--;
                    break;
                }

                //next word
                if (curCharLen + words[curEndPos].size() > L)
                {
                    curEndPos--;
                    break;
                }

                curCharLen += words[curEndPos].size();
                curWordNum++; curWordCharLen += words[curEndPos].size();

                curEndPos++;
            }

            if (curEndPos >= n - 1)
            {
                assignLineContentLeftJustified(curLine, words, curStartPos, curStartPos + curWordNum - 1);
                spaceNum = L - curWordCharLen - (curWordNum - 1);
                for (int i = 0; i < spaceNum; i++)
                    curLine += " ";
            }                
            else
            {
                if (curWordNum == 1)
                {
                    curLine = words[curStartPos];
                    for (int i = 0; i < L - curWordCharLen; i++)
                        curLine += " ";
                }
                else
                {
                    spaceNum = L - curWordCharLen;
                    avgSpaceNum = spaceNum / (curWordNum - 1);
                    residuleSpaceNum = spaceNum - avgSpaceNum*(curWordNum - 1);
                    assignLineContentEvenJustified(curLine, words, curStartPos, curStartPos + curWordNum - 1,
                        avgSpaceNum, residuleSpaceNum);
                }                
            }

            result.push_back(curLine);

            curStartPos = curEndPos + 1;
        }

        return result;
    }

private:
    inline void assignLineContentLeftJustified(string& line, const vector<string> &words,
        int start, int end)
    {
        line = words[start];
        for (int i = start + 1; i <= end; i++)
        {
            line += " ";
            line += words[i];
        }
    }

    inline void assignLineContentEvenJustified(string& line, const vector<string> &words,
        int start, int end, int avgSpaceNum, int residuleSpaceNum)
    {
        line = words[start];
        for (int i = start + 1; i <= end; i++)
        {
            for (int j = 0; j < avgSpaceNum; j++)
                line += " ";
            if (residuleSpaceNum)
            {
                line += " ";
                residuleSpaceNum--;
            }
            line += words[i];
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<string>  words;
    vector<string>  result;
    int L = 16;

    words.push_back("This");
    words.push_back("is");
    words.push_back("an");
    words.push_back("example");
    words.push_back("of");
    words.push_back("text");
    words.push_back("justification.");

    Solution so;
    result = so.fullJustify(words, L);

    for (int i = 0; i < result.size(); i++)
        printf("%s\n", result[i].c_str());

    system("PAUSE");
	return 0;
}

