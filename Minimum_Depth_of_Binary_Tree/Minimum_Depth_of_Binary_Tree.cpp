// Minimum_Depth_of_Binary_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <queue>
#include <assert.h>

using namespace std;

#define INVALID_TREE_ERROR -1

typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {
public:
    int minDepth(TreeNode *root) {
        if (root == NULL)
            return 0;

        queue<TreeNode*> q1;
        queue<TreeNode*> q2;
        queue<TreeNode*> *curQ  = &q1;
        queue<TreeNode*> *nextQ = &q2;
        queue<TreeNode*> *tempQ;

        TreeNode* curNode;
        int curDepth = 0;
        curQ->push(root);

        while (!curQ->empty())
        {
            curDepth++;
            assert(nextQ->empty());

            while (!curQ->empty())
            {
                curNode = curQ->front();
                curQ->pop();

                if (curNode->left == NULL && curNode->right == NULL)
                    return curDepth;

                if (curNode->left)
                    nextQ->push(curNode->left);
                if (curNode->right)
                    nextQ->push(curNode->right);
            }

            tempQ = curQ;
            curQ = nextQ;
            nextQ = tempQ;
        }

        assert(0); //should never be here
        return INVALID_TREE_ERROR;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

