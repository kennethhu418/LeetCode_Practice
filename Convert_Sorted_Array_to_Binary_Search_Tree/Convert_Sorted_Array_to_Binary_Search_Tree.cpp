// Convert_Sorted_Array_to_Binary_Search_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>
#include <stack>

using namespace std;

 typedef struct __TreeNode {
     int val;
     __TreeNode *left;
     __TreeNode *right;
     __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 }TreeNode;

 typedef struct __StackElem {
     TreeNode *root;
     TreeNode* leftTree;
     TreeNode* rightTree;
     int                start;
     int                end;
     int                visitStep; //0: entry 1: visited left 2: visited right
 }StackElem;

class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &num) {
        //return sortedArrayToBST(num, 0, num.size() - 1);
        return sortedArrayToBST_NonRecursive(num);
    }

private:
    TreeNode *sortedArrayToBST(const vector<int> &num, int start, int end) {
        if (start > end)    return NULL;

        TreeNode* root = new TreeNode(0);
        assert(root);

        if (start == end)
        {
            root->val = num[start];
            return root;
        }

        int rootIndex = (end + start + 1) / 2;
        root->val = num[rootIndex];
        

        TreeNode* leftTree = NULL, *rightTree = NULL;
        
        if (start < rootIndex )
            leftTree = sortedArrayToBST(num, start, rootIndex - 1);
        if (end > rootIndex)
            rightTree = sortedArrayToBST(num, rootIndex + 1, end);

        root->left = leftTree; root->right = rightTree;
        return root;
    }


    TreeNode *sortedArrayToBST_NonRecursive(const vector<int> &num) {
        int     size = num.size();
        if (size == 0)
            return NULL;

        StackElem   e = {NULL, NULL, NULL, 0, size - 1, 0};
        stack<StackElem>    stackA;
        stackA.push(e);

        while (!stackA.empty())
        {
            e = stackA.top();
            stackA.pop();

            if (e.visitStep == 0)
            {
                TreeNode* curRoot = new TreeNode(0);
                assert(curRoot);
                e.root = curRoot;

                if (e.start == e.end)
                {
                    curRoot->val = num[e.start];
                    if (!stackA.empty())
                    {
                        if (stackA.top().visitStep == 1)
                            stackA.top().leftTree = curRoot;
                        else
                        {
                            assert(stackA.top().visitStep == 2);
                            stackA.top().rightTree = curRoot;
                        }
                    }
                    continue;                    
                }

                int rootIndex = (e.end + e.start + 1) / 2;
                curRoot->val = num[rootIndex];

                e.visitStep = 1;
                stackA.push(e);

                if (e.start == rootIndex)
                    continue;

                e.end = rootIndex - 1;
                e.leftTree = e.rightTree = e.root = NULL;
                e.visitStep = 0;
                stackA.push(e);
            }
            else if (e.visitStep == 1)
            {
                e.visitStep = 2;
                stackA.push(e);

                int rootIndex = (e.end + e.start + 1) / 2;
                if (rootIndex < e.end)
                {
                    e.start = rootIndex + 1;
                    e.leftTree = e.rightTree = e.root = NULL;
                    e.visitStep = 0;
                    stackA.push(e);
                }
            }
            else if (e.visitStep == 2)
            {
                e.root->left = e.leftTree; e.root->right = e.rightTree;
                if (!stackA.empty())
                {
                    if (stackA.top().visitStep == 1)
                        stackA.top().leftTree = e.root;
                    else
                    {
                        assert(stackA.top().visitStep == 2);
                        stackA.top().rightTree = e.root;
                    }
                }
            }
            else
                assert(0); //should never be larger than 2.
        }

        return e.root;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

