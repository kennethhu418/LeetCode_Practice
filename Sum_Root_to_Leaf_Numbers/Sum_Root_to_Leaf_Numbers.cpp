// Sum_Root_to_Leaf_Numbers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define DEFAULT_STACK_SIZE 200

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

 typedef struct __TreeNode {
     int val;
     __TreeNode *left;
     __TreeNode *right;
     __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 }TreeNode;

typedef struct _StackElem
{
    int    step;  //0: left tree  1: right tree
    int    curPathNumber;
    TreeNode* node;
}StackElem;

class Solution {
public:
    int sumNumbers(TreeNode *root) {
        int     totalNum = 0;
        if (root == NULL)
        {
            return totalNum;
        }

        StackElem elem = {0, 0, root};
        int pathNumber = 0;

        stack.Push(elem);
        while (!stack.IsEmpty())
        {
            switch (stack.Peak().step)
            {
            case 0:
                if (stack.Peak().node == NULL)
                {
                    stack.Pop(elem);
                    break;
                }

                pathNumber = stack.Peak().curPathNumber * 10 + stack.Peak().node->val;

                if (stack.Peak().node->left == NULL && stack.Peak().node->right == NULL)
                {                    
                    totalNum += pathNumber;
                    stack.Pop(elem);
                    break;
                }

                stack.Peak().step = 1;

                if (stack.Peak().node->left != NULL)
                {                    
                    elem.curPathNumber = pathNumber;
                    elem.node = stack.Peak().node->left;
                    elem.step = 0;
                    stack.Push(elem);
                }

                break;                
            case 1:
                pathNumber = stack.Peak().curPathNumber * 10 + stack.Peak().node->val;
                stack.Peak().step = 2;

                if (stack.Peak().node->right != NULL)
                {
                    elem.curPathNumber = pathNumber;
                    elem.node = stack.Peak().node->right;
                    elem.step = 0;
                    stack.Push(elem);
                }

                break;

            case 2:
                stack.Pop(elem);
                break;
            default:
                break;
            }
        }

        return totalNum;
                
    }

private:
    MyStack<StackElem> stack;
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

