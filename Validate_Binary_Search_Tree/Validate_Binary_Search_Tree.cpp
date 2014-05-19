// Validate_Binary_Search_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"




typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {
public:
    bool isValidBST(TreeNode *root) {
        int minVal = 0, maxVal = 0;

        return isValidBSTWithEndValues(root, minVal, maxVal);
    }

private:
    bool isValidBSTWithEndValues(TreeNode* root, int &minVal, int &maxVal)
    {
        if (root == NULL)
            return true;

        minVal = maxVal = root->val;

        int childMinVal, childMaxVal;

        if (root->left)
        {
            if (!isValidBSTWithEndValues(root->left, childMinVal, childMaxVal))
                return false;

            if (root->val <= childMaxVal)
                return false;

            minVal = childMinVal;
        }

        if (root->right)
        {
            if (!isValidBSTWithEndValues(root->right, childMinVal, childMaxVal))
                return false;

            if (root->val >= childMinVal)
                return false;

            maxVal = childMaxVal;
        }

        return true;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

