// Binary_Tree_Postorder_Traversal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

using namespace std;


typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

typedef struct __Elem
{
    char        step;
    TreeNode*   node;
}Elem;

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
            delete [] arr;
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

        return arr[top-1];
    }

private:
    T*  arr;
    int maxSize;
    int top;
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> traverseResult;

        if (root == NULL)
        {
            return traverseResult;
        }

        MyStack<Elem> stack(100);
        Elem frame = {0, root};
        stack.Push(frame);

        while(!stack.IsEmpty())
        {
            if (stack.Peak().node == NULL)
            {
                stack.Pop(frame);
                continue;
            }

            if (stack.Peak().step == 0) //it is time to visit left tree
            {
                stack.Peak().step = 1;
                frame.step = 0;
                frame.node = stack.Peak().node->left;
                stack.Push(frame);
                continue;                
            }

            if (stack.Peak().step == 1) //it is time to visit right tree
            {
                stack.Peak().step = 2;
                frame.step = 0;
                frame.node = stack.Peak().node->right;
                stack.Push(frame);
                continue;                
            }

            stack.Pop(frame);

            traverseResult.push_back(frame.node->val);
        }

        return traverseResult;
        
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

