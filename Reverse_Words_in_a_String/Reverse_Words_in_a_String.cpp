// LeetCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Solution {
public:
    void reverseWords(string &s) {

        if(s[0] == '\0')
            return;

        //First remove residule spaces
        removeResiduleSpace(s);

        //Then reverse each word in the sentense
        reverseEachWord(s);

        //Last reverse the whole string
        reverseStr(s);

        const char* str = s.c_str();
        s = str;
    }

private:

    inline void reverseStr(char* start, char* end)
    {
        char tmp;
        if(start == NULL || end == NULL || start > end)
            return;

        while(start < end)
        {
            tmp = *start;
            *start = *end;
            *end = tmp;
            start++;
            end--;
        }

    }

    void reverseStr(string& s)
    {
        char* start = &(s[0]);
        char* end = NULL;

        while(*start != '\0')
            start++;
        end = start - 1;
        start = &(s.at(0));

        reverseStr(start, end);
    }

    void reverseEachWord(string& s)
    {
        char* start = &(s[0]);
        char* end = NULL;
        char* currentTpos = start;

        while(*currentTpos != '\0')
        {
            if(*currentTpos != ' ')
            {
                currentTpos++;
                continue;
            }

            end = currentTpos - 1;
            reverseStr(start, end);
            currentTpos++;
            start = currentTpos;
            end = NULL;
        }

        end = currentTpos - 1;
        reverseStr(start, end);
    }



    void removeResiduleSpace(string &s)
    {
        char* currentTpos = &(s[0]);
        char* currentApos = currentTpos;
        char* currentStrpos = NULL;

        if(s[0] == '\0')
            return;

        while(*currentTpos != '\0')
        {
            if(*currentTpos == ' ')
            {
                currentTpos++;
                continue;
            }

            if(currentStrpos == NULL)
                currentStrpos = currentTpos;

            if(*(currentTpos+1) == ' ' || *(currentTpos+1) == '\0')
            {
                if(currentStrpos == currentApos)
                    currentApos = currentTpos + 1;
                else
                {
                    while(currentStrpos <= currentTpos)
                        *(currentApos++) = *(currentStrpos++);
                }

                if(*(currentTpos+1) == ' ')
                    *(currentApos++) = ' ';
                else
                    break;

                currentTpos += 2;
                currentStrpos = NULL;
                continue;
            }

            currentTpos++;
        } // end while

        *currentApos = '\0';

        if(*(currentApos-1) == ' ')
            *(currentApos-1) = '\0';

    }


};

int _tmain(int argc, _TCHAR* argv[])
{
    string temp = " I am  a little      boy who   is in EMC     ";
    string expected = "EMC in is who boy little a am I";
    Solution solution;

    solution.reverseWords(temp);

    if(temp == expected)
        printf("Success!\n");

    printf("%s\n", temp.c_str());

    system("PAUSE");

    return 0;
}