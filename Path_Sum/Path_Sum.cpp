// Path_Sum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        int curSum = 0;

        return hasPathSum(root, curSum, sum);
    }

private:
    bool hasPathSum(TreeNode *curNode, int &curSum, const int &sum)
    {
        if (curNode == NULL)
            return false;

        if (curNode->left == NULL && curNode->right == NULL)
        {
            if (curSum + curNode->val == sum)
                return true;
            return false;
        }

        curSum += curNode->val;

        if (curNode->left && hasPathSum(curNode->left, curSum, sum))
        {
            curSum -= curNode->val;
            return true;
        }

        if (curNode->right && hasPathSum(curNode->right, curSum, sum))
        {
            curSum -= curNode->val;
            return true;
        }

        curSum -= curNode->val;

        return false;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

