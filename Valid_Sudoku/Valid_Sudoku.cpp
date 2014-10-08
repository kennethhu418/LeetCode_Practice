// Valid_Sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <vector>

using std::vector;

#define SUDOKU_SIZE 9 

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        unsigned short rowBitMask[SUDOKU_SIZE * 3] = { 0 };
        unsigned short *colBitMask = &rowBitMask[SUDOKU_SIZE], *blockBitMask = &rowBitMask[SUDOKU_SIZE << 1];

        int i = 0, j = 0, blk = -1, curNum = 0;
        for (i = 0; i < SUDOKU_SIZE; ++i){
            for (j = 0; j < SUDOKU_SIZE; ++j){
                if (board[i][j] == '.') continue;
                blk = (i / 3) * 3 + j / 3;
                curNum = board[i][j] - '0';
                //check row mask
                if (rowBitMask[i] & (1 << curNum)) return false;
                rowBitMask[i] |= (1 << curNum);
                //check column mask
                if (colBitMask[j] & (1 << curNum)) return false;
                colBitMask[j] |= (1 << curNum);
                //check block mask
                if (blockBitMask[blk] & (1 << curNum)) return false;
                blockBitMask[blk] |= (1 << curNum);
            }
        }

        return true;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

