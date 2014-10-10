// Letter_Combinations_of_a_Phone_Number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>

using std::string;
using std::vector;

static const unsigned int MAP_COUNT = 4;
typedef struct __DigitMappingRecord
{
    int     count;
    char    mapping[MAP_COUNT];
}DigitMappingRecord;

static const DigitMappingRecord mappingArr[10] = {
    { 1, { ' ' } }, //0
    { 1, { ' ' } }, //1
    { 3, { 'a', 'b', 'c' } }, //2
    { 3, { 'd', 'e', 'f' } }, //3
    { 3, { 'g', 'h', 'i' } }, //4
    { 3, { 'j', 'k', 'l' } }, //5
    { 3, { 'm', 'n', 'o' } }, //6
    { 4, { 'p', 'q', 'r', 's' } }, //7
    { 3, { 't', 'u', 'v' } }, //8
    { 4, { 'w', 'x', 'y', 'z' } }, //9
};

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> resultArr;
        int n = digits.size();
        if (n == 0){
            resultArr.push_back(""); return resultArr;
        }

        int *indexArr = new int[n];
        indexArr[0] = 0;

        int curDigit = 0, curNum = 0;
        string singleComb(n, 'a');
        while (curDigit >= 0){
            if (curDigit == n){
                resultArr.push_back(singleComb);
                ++indexArr[--curDigit];
                continue;
            }

            curNum = digits[curDigit] - '0';
            if (indexArr[curDigit] == mappingArr[curNum].count){
                if (curDigit > 0) ++indexArr[curDigit - 1];
                --curDigit;
                continue;
            }

            singleComb[curDigit] = mappingArr[curNum].mapping[indexArr[curDigit]];
            ++curDigit;
            if (curDigit < n) indexArr[curDigit] = 0;
        }

        delete[] indexArr;
        return resultArr;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    string strnums;

    Solution so;
    vector<string> result;
    vector<string>::const_iterator iter;
    while (std::cin >> strnums)
    {
        result = so.letterCombinations(strnums);
        for (iter = result.begin(); iter != result.end(); iter++)
            std::cout << *iter << " ";
        std::cout << std::endl << std::endl;
    }

	return 0;
}

