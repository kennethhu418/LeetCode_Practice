// Construct_Binary_Tree_from_Postorder_and_Inorder_Traversal.cpp : 定义控制台应用程序的入口点。
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
    int post_start;
    int post_end;
    int in_start;
    int in_end;
    TreeNode* parent;
    char isLeftTree;
}QElem;

class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        int size = postorder.size();
        assert(size == inorder.size());

        if (size == 0)
            return NULL;

        queue<QElem>    queueA;
        QElem curElem = { 0, size - 1, 0, size - 1, NULL, true }, newElem;
        queueA.push(curElem);


        TreeNode* root;
        TreeNode* finalRoot = NULL;
        int rootInPos = 0;

        while (!queueA.empty())
        {
            curElem = queueA.front();
            queueA.pop();

            root = new TreeNode(postorder[curElem.post_end]);
            if (finalRoot == NULL)
                finalRoot = root;
            if (curElem.parent)
            {
                if (curElem.isLeftTree)
                    curElem.parent->left = root;
                else
                    curElem.parent->right = root;
            }

            rootInPos = findInPos(inorder, postorder[curElem.post_end], curElem.in_start, curElem.in_end);
            assert(rootInPos >= 0);

            int leftTreeNodeNum = rootInPos - curElem.in_start;
            int rightTreeNodeNum = curElem.in_end - rootInPos;

            if (leftTreeNodeNum)
            {
                newElem.post_start = curElem.post_start;
                newElem.post_end = curElem.post_start + leftTreeNodeNum - 1;
                newElem.in_start = curElem.in_start;
                newElem.in_end = rootInPos - 1;
                newElem.parent = root;
                newElem.isLeftTree = true;
                queueA.push(newElem);
            }

            if (rightTreeNodeNum)
            {
                newElem.post_start = curElem.post_start + leftTreeNodeNum;
                newElem.post_end = curElem.post_end - 1;
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

