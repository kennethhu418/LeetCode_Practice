// Surrounded_Regions.cpp : 定义控制台应用程序的入口点。
//

/***********************************************************************
        Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

        A region is captured by flipping all 'O's into 'X's in that surrounded region.

        For example,
        X X X X
        X O O X
        X X O X
        X O X X

        After running your function, the board should be :

        X X X X
        X X X X
        X X X X
        X O X X
***********************************************************************/

#include "stdafx.h"
#include <vector>

using namespace std;

class Solution {
public:
    void solve(vector<vector<char>> &board) {
        int     n = board.size();
        if (n < 3)
            return;

        int     m = board.at(0).size();
        if (m < 3)
            return;

        /************************************************************************
          This is recursive solution. We need to change it to non-recursive solution like below
          ************************************************************************          
        //First infect dead to neighbors from edge nodes
        for (int j = 0; j < m; j++)
        {
            if (board.at(0).at(j) == 'O')
                InfectDeadToNeighbors(board, 0, j);
            if (board.at(n - 1).at(j) == 'O')
                InfectDeadToNeighbors(board, n - 1, j);
        }
        for (int j = 0; j < n; j++)
        {
            if (board.at(j).at(0) == 'O')
                InfectDeadToNeighbors(board, j, 0);
            if (board.at(j).at(m - 1) == 'O')
                InfectDeadToNeighbors(board, j, m - 1);
        }
        ************************************************************************/

        InfectDeadToNeighborsNonRecursive(board);

        //Now all internal 'O's which are surrounded by X are still X, while
        //the Os whose region is open to ourside of the board is marked 'D'
        //So here just change 'O' to 'X' and 'D' to 'O'
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board.at(i).at(j) == 'O')
                    board.at(i).at(j) = 'X';
                else if (board.at(i).at(j) == 'D')
                    board.at(i).at(j) = 'O';
            }
        }

    }


private:

    bool HasInfectedNeighbor(vector<vector<char>> &board, int x, int y)
    {
        int n = board.size();
        if (n == 0)
            return false;

        int m = board.at(0).size();
        if (m == 0)
            return false;

        if (x >= n || y >= m)
            return false;

        if (y - 1 >= 0 && board[x][y - 1] == 'D')
            return true;        
        if (y + 1 < m && board[x][y + 1] == 'D')
            return true;
        if (x - 1 >= 0 && board[x-1][y] == 'D')
            return true;
        if (x + 1 < n && board[x+1][y] == 'D')
            return true;

        return false;
    }

    void InfectDeadToNeighborsNonRecursive(vector<vector<char>> &board)
    {
        int  n = board.size();
        if (n == 0)
            return;

        int     m = board.at(0).size();
        if (m == 0)
            return;

        //Mark  the most outside edge nodes as dead
        for (int j = 0; j < m; j++)
        {
            if (board.at(0).at(j) == 'O')
                board.at(0).at(j) = 'D';
            if (board.at(n - 1).at(j) == 'O')
                board.at(n - 1).at(j) = 'D';
        }
        for (int j = 0; j < n; j++)
        {
            if (board.at(j).at(0) == 'O')
                board.at(j).at(0) = 'D';
            if (board.at(j).at(m - 1) == 'O')
                board.at(j).at(m - 1) = 'D';
        }

        //Now enter inside nodes circle by circle
        int startx = 1, starty = 1;
        int size_x = n - 2, size_y = m - 2;

        while (size_x > 0 && size_y > 0)
        {
            for (int i = 0; i < size_y; i++)
            {
                if (board[startx][starty + i] == 'O' && HasInfectedNeighbor(board, startx, starty + i))
                    board[startx][starty+i] = 'D';
                if (board[startx + size_x - 1][starty + i] == 'O' && HasInfectedNeighbor(board, startx + size_x - 1, starty + i))
                    board[startx + size_x - 1][starty + i] = 'D';
            }

            for (int i = 0; i < size_x; i++)
            {
                if (board[startx + i][starty] == 'O' && HasInfectedNeighbor(board, startx + i, starty))
                    board[startx + i][starty] = 'D';
                if (board[startx + i][starty + size_y - 1] == 'O' && HasInfectedNeighbor(board, startx + i, starty + size_y - 1))
                    board[startx + i][starty + size_y - 1] = 'D';
            }

            startx += 1;
            starty += 1;
            size_x -= 2;
            size_y -= 2;
        }
    }

    void InfectDeadToNeighbors(vector<vector<char>> &board, int x, int y)
    {
        int     n = board.size();
        if (n == 0)
            return;

        int     m = board.at(0).size();
        if (m == 0)
            return;

        board.at(x).at(y) = 'D';

        //infect left
        if (y - 1 >= 0 && board.at(x).at(y - 1) == 'O')
            InfectDeadToNeighbors(board, x, y-1);

        //infect right
        if (y + 1 < m && board.at(x).at(y + 1) == 'O')
            InfectDeadToNeighbors(board, x, y + 1);

        //infect down
        if (x + 1 < n && board.at(x+1).at(y) == 'O')
            InfectDeadToNeighbors(board, x+1, y);

        //infect up
        if (x -1 >= 0 && board.at(x - 1).at(y) == 'O')
            InfectDeadToNeighbors(board, x - 1, y);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

