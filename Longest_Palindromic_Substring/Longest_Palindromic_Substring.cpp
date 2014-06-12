// Longest_Palindromic_Substring.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::vector;
using std::string;

#define size_t  std::size_t
#define INVALID_CHAR  '@'

//第一版本的算法的时间复杂度是O(n^2)且空间复杂度也是O(n^2)
//这里我们采用时间复杂度和空间复杂度均为O(n)的解法
//此算法称为 Manacher’s algorithm，whose detail description can be found @
//http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
//,which is also attached in the project
class Solution {
public:
    string longestPalindrome(const string &s) {
        size_t n = s.size();
        if (n < 2) return s;

        convertString(s);

        size_t  center = 0, rightBounder = 0, mirrorPos = 0;
        radiusArray[0] = 0;

        for (size_t i = 1; i < TSize; i++)
        {
            radiusArray[i] = 0;

            if (i <= rightBounder)
            {
                mirrorPos = 2 * center - i;

                if (i + radiusArray[mirrorPos] < rightBounder) //PAY ATTENTION: CANNOT BE <=
                {
                    radiusArray[i] = radiusArray[mirrorPos];
                    continue;
                }

                radiusArray[i] = rightBounder - i;
                extendRadius(i, rightBounder + 1);

                if (i + radiusArray[i] <= rightBounder)
                    continue;

                center = i;
                rightBounder = i + radiusArray[i];
            }
            else
            {
                center = i;
                extendRadius(i, i + 1);
                rightBounder = i + radiusArray[i];
            }            
        }

        center = findMaxValPos();
        int startPos = (center - radiusArray[center])/2;
        int size = radiusArray[center];

        radiusArray.clear();
        T.clear();

        return s.substr(startPos, size);
    }

private:
    string     T;
    size_t      TSize;
    vector<size_t>  radiusArray;

    void convertString(const string& s)
    {
        T = INVALID_CHAR;
        size_t n = s.size();

        for (size_t i = 0; i < n; i++)
        {
            T += s[i];
            T += INVALID_CHAR;
        }

        TSize = T.size();
        radiusArray.resize(TSize);
    }

    inline void extendRadius(size_t center, size_t startPos)
    {
        size_t mirror = 0;
        while (2 * center >= startPos && startPos < TSize)
        {
            mirror = 2 * center - startPos;
            if (T[mirror] == T[startPos])
            {
                radiusArray[center]++;
                startPos++;
            }
            else
                break;
        }
    }

    size_t findMaxValPos()
    {
        int maxVal = radiusArray[0], maxValPos = 0;
        for (size_t i = 1; i < TSize; i++)
        {
            if (maxVal < radiusArray[i])
            {
                maxVal = radiusArray[i];
                maxValPos = i;
            }
        }

        return maxValPos;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Solution so;

    string srcStr;
    
    while (std::cin >> srcStr)
    {
        std::cout << so.longestPalindrome(srcStr) << std::endl<<std::endl;
    }

	return 0;
}

