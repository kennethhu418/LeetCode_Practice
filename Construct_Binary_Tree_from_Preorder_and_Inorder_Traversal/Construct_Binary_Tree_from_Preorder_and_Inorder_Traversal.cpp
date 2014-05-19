// Construct_Binary_Tree_from_Preorder_and_Inorder_Traversal.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>
#include <queue>

using namespace std;

typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

typedef struct __QElem
{
    int pre_start;
    int pre_end;
    int in_start;
    int in_end;
    TreeNode* parent;
    char isLeftTree;
}QElem;

class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int size = preorder.size();
        assert(size == inorder.size());

        if (size == 0)
            return NULL;

        queue<QElem>    queueA;
        QElem curElem = {0, size-1, 0, size-1, NULL, true}, newElem;
        queueA.push(curElem);


        TreeNode* root;
        TreeNode* finalRoot = NULL;
        int rootInPos = 0;

        while (!queueA.empty())
        {
            curElem = queueA.front();
            queueA.pop();

            root = new TreeNode(preorder[curElem.pre_start]);
            if (finalRoot == NULL)
                finalRoot = root;
            if (curElem.parent)
            {
                if (curElem.isLeftTree)
                    curElem.parent->left = root;
                else
                    curElem.parent->right = root;
            }

            rootInPos = findInPos(inorder, preorder[curElem.pre_start], curElem.in_start, curElem.in_end);
            assert(rootInPos >= 0);

            int leftTreeNodeNum = rootInPos - curElem.in_start;
            int rightTreeNodeNum = curElem.in_end - rootInPos;

            if (leftTreeNodeNum)
            {
                newElem.pre_start = curElem.pre_start + 1;
                newElem.pre_end = curElem.pre_start + leftTreeNodeNum;
                newElem.in_start = curElem.in_start;
                newElem.in_end = rootInPos - 1;
                newElem.parent = root;
                newElem.isLeftTree = true;
                queueA.push(newElem);
            }

            if (rightTreeNodeNum)
            {
                newElem.pre_start = curElem.pre_start + 1 + leftTreeNodeNum;
                newElem.pre_end = curElem.pre_end;
                newElem.in_start = rootInPos + 1;
                newElem.in_end = curElem.in_end;
                newElem.parent = root;
                newElem.isLeftTree = false;
                queueA.push(newElem);
            }
        }

        return finalRoot;        
    }

private:
    inline int findInPos(const vector<int> &array, int target, int start, int end)
    {
        int cur = start;
        while (cur <= end)
        {
            if (array[cur] == target)
                return cur;
            cur++;
        }

        return -1;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

