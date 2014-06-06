// Sudoku_Solver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <vector>

using std::vector;

class Solution {
public:
    void solveSudoku(vector<vector<char> > &board) {
        assert(board.size() == 9 && board[0].size() == 9);

        InitializeSudokuAcc(board);

        int x, y;
        bool hasBlank = getNextBlankPos(board, 0, 0, x, y);

        if (!hasBlank)
            return;

        solveSudoku(board, x, y);
        return;
    }

private:
    bool    rowAcc[9][9];
    bool    colAcc[9][9];
    bool    blockAcc[9][9];

    bool solveSudoku(vector<vector<char> > &board, int x, int y)
    {
        int blockIndex = getBlockIndex(x, y);
        int nextX, nextY;
        bool haveNextBlank = getNextBlankPos(board, x, y + 1, nextX, nextY);

        for (int curNum = 0; curNum < 9; curNum++)
        {
            if (rowAcc[x][curNum] || colAcc[y][curNum] || blockAcc[blockIndex][curNum])
                continue;

            board[x][y] = curNum + 1 + '0';
            rowAcc[x][curNum] = colAcc[y][curNum] = blockAcc[blockIndex][curNum] = true;

            if (!haveNextBlank || solveSudoku(board, nextX, nextY))
                return true;

            rowAcc[x][curNum] = colAcc[y][curNum] = blockAcc[blockIndex][curNum] = false;
            board[x][y] = '.';
        }
        
        return false;
    }

    inline int getBlockIndex(int x, int y)
    {
        return 3 * (x / 3) + y / 3;
    }

    inline void InitializeSudokuAcc(vector<vector<char> > &board)
    {
        for (int i = 0; i < 9; i++)
        {
            memset(rowAcc[i], 0, sizeof(bool)*9);
            memset(colAcc[i], 0, sizeof(bool)* 9);
            memset(blockAcc[i], 0, sizeof(bool)* 9);
        }

        int blockIndex = 0;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')
                    continue;

                blockIndex = getBlockIndex(i, j);
                rowAcc[i][board[i][j] - 1 - '0'] = true;
                colAcc[j][board[i][j] - 1 - '0'] = true;
                blockAcc[blockIndex][board[i][j] - 1 - '0'] = true;
            }
        }
    }

    inline bool getNextBlankPos(vector<vector<char> > &board, int x, int y, int& nextX, int& nextY)
    {
        for (int i = x; i < 9; i++)
        {
            for (int j = y; j < 9; j++)
            {
                if (board[i][j] == '.')
                {
                    nextX = i; nextY = j;
                    return true;
                }
            }

            y = 0;
        }

        return false;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<char> v1(9, '.');
    vector<char> v2(9, '.');
    vector<char> v3(9, '.');
    vector<char> v4(9, '.');
    vector<char> v5(9, '.');
    vector<char> v6(9, '.');
    vector<char> v7(9, '.');
    vector<char> v8(9, '.');
    vector<char> v9(9, '.');
    vector<vector<char> > board;

    v1[5] = 7;
    v1[8] = 9;

    v2[1] = 4;
    v2[4] = 8;
    v2[5] = 1;



	return 0;
}

