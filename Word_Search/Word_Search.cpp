// Word_Search.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        int m = board.size();
        if (m == 0)
            return false;
        int n = board[0].size();
        if (n == 0)
            return false;

        if (word.size() == 0)
            return false;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    if (exist(board, m, n, word, i, j, 0))
                        return true;
                }
            }
        }

        return false;
    }

private:
    inline  void ChangeLetter(char& c)
    {
        if (c >= 'a')
            c = 26 + c - 'a';
        else
            c = c - 'A';
    }

    inline  void ResumeLetter(char& c)
    {
        if (c >= 26)
            c = c + 'a' - 26;
        else
            c = c + 'A';
    }

    bool exist(vector<vector<char> > &board, int m, int n, string &word, int x, int y, int curC)
    {
        if (curC == word.size() - 1)
            return true;

        ChangeLetter(board[x][y]);

        if (x - 1 >= 0 && board[x - 1][y] == word[curC + 1])
        {
            if (exist(board, m, n, word, x - 1, y, curC + 1))
            {
                ResumeLetter(board[x][y]);
                return true;
            }
        }

        if (x + 1 < m && board[x + 1][y] == word[curC + 1])
        {
            if (exist(board, m, n, word, x + 1, y, curC + 1))
            {
                ResumeLetter(board[x][y]);
                return true;
            }
        }

        if (y - 1 >= 0 && board[x][y - 1] == word[curC + 1])
        {
            if (exist(board, m, n, word, x, y - 1, curC + 1))
            {
                ResumeLetter(board[x][y]);
                return true;
            }
        }

        if (y + 1 < n  && board[x][y + 1] == word[curC + 1])
        {
            if (exist(board, m, n, word, x, y + 1, curC + 1))
            {
                ResumeLetter(board[x][y]);
                return true;
            }
        }

        ResumeLetter(board[x][y]);
        return false;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

