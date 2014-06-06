// Valid_Sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <vector>

using std::vector;

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        assert(board.size() == 9 && board[0].size() == 9);

        for (int i = 0; i < 9; i++)
        {
            memset(rowAcc[i], 0, sizeof(bool)* 9);
            memset(colAcc[i], 0, sizeof(bool)* 9);
            memset(blockAcc[i], 0, sizeof(bool)* 9);
        }

        int blockIndex = -1;
        int curNum;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')
                    continue;

                blockIndex = getBlockIndex(i, j);
                curNum = board[i][j] - '0' - 1;
                if (rowAcc[i][curNum] || colAcc[j][curNum] || blockAcc[blockIndex][curNum])
                    return false;
                
                rowAcc[i][curNum] = colAcc[j][curNum] = blockAcc[blockIndex][curNum] = true;
            }
        }

        return true;
    }

private:
    bool    rowAcc[9][9];
    bool    colAcc[9][9];
    bool    blockAcc[9][9];

    inline int getBlockIndex(int x, int y)
    {
        return 3 * (x / 3) + y / 3;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

