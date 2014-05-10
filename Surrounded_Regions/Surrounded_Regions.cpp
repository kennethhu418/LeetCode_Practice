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

#define DEFAULT_STACK_SIZE 30

template <class T>
class MyStack
{
public:
    MyStack(int size = DEFAULT_STACK_SIZE)
    {
        this->maxSize = size;
        arr = new T[size];
        top = 0;
    }

    ~MyStack()
    {
        if (arr)
        {
            delete[] arr;
        }
    }

    bool Push(T elem)
    {
        if (top == maxSize)
        {
            return false;
        }

        arr[top++] = elem;
        return true;
    }

    bool Pop(T& elem)
    {
        if (top == 0)
        {
            return false;
        }

        elem = arr[--top];
        return true;
    }

    bool IsEmpty()
    {
        return (top == 0);
    }

    bool IsFull()
    {
        return (top == maxSize);
    }

    T& Peak()
    {
        T e;
        if (IsEmpty())
        {
            return e;
        }

        return arr[top - 1];
    }

private:
    T*  arr;
    int maxSize;
    int top;
};

typedef struct _StackElem
{
    int    step;
    int       x;
    int       y;
}StackElem;

class Solution {
public:
    Solution()
    {
        stack = new MyStack<StackElem>(300000);
    }

    ~Solution()
    {
        delete stack;
    }

    void solve(vector<vector<char>> &board) {
        int     n = board.size();
        if (n < 3)
            return;

        int     m = board.at(0).size();
        if (m < 3)
            return;
 
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
    MyStack<StackElem> * stack;

    void InfectDeadToNeighborsNonRecursive(vector<vector<char>> &board, int x, int y)
    {
        int     n = board.size();
        if (n == 0)
            return;

        int     m = board.at(0).size();
        if (m == 0)
            return;

        StackElem elem = { 1, x, y };
        stack->Push(elem);

        while (!stack->IsEmpty())
        {
           x = stack->Peak().x;
           y = stack->Peak().y;

           switch (stack->Peak().step)
           {
           case 0:
               stack->Pop(elem);

               break;
           case 1:
               board.at(x).at(y) = 'D';

               //infect left
               stack->Peak().step = 2;
               if (y - 1 >= 0 && board.at(x).at(y - 1) == 'O')  //step1
               {
                   elem.step = 1;
                   elem.x = x;
                   elem.y = y - 1;
                   stack->Push(elem);
               }

               break;
           case 2:

               //infect right
               stack->Peak().step = 3;
               if (y + 1 < m && board.at(x).at(y + 1) == 'O')  //step2
               {                   
                   elem.step = 1;
                   elem.x = x;
                   elem.y = y + 1;
                   stack->Push(elem);
               }

               break;
           case 3:
               //infect down
               stack->Peak().step = 4;
               if (x + 1 < n && board.at(x + 1).at(y) == 'O')  //step3
               {
                   elem.step = 1;
                   elem.x = x + 1;
                   elem.y = y;
                   stack->Push(elem);
               }

               break;
           case 4:

               //infect up
               stack->Peak().step = 0;
               if (x - 1 >= 0 && board.at(x - 1).at(y) == 'O')  //step4
               {                  
                   elem.step = 1;
                   elem.x = x - 1;
                   elem.y = y;
                   stack->Push(elem);
               }
               break;
           default:
               break;
           }
        }

        return;
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
        if (y - 1 >= 0 && board.at(x).at(y - 1) == 'O')  //step1
            InfectDeadToNeighbors(board, x, y-1);

        //infect right
        if (y + 1 < m && board.at(x).at(y + 1) == 'O')  //step2
            InfectDeadToNeighbors(board, x, y + 1);

        //infect down
        if (x + 1 < n && board.at(x+1).at(y) == 'O')  //step3
            InfectDeadToNeighbors(board, x+1, y);

        //infect up
        if (x -1 >= 0 && board.at(x - 1).at(y) == 'O')  //step4
            InfectDeadToNeighbors(board, x - 1, y);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

