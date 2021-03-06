// Binary_Tree_Maximum_Path_Sum.cpp : Defines the entry point for the console application.
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
    int maxPathSum(TreeNode *root) {
        maxLen = 0 - 0x1FFFFFFF;

        if (root == NULL)
            return 0;
        if (root->left == NULL && root->right == NULL)
            return root->val;

        int maxSingleSideLen;
        maxPathSumRecursion(root, maxSingleSideLen);

        return maxLen;

    }

private:
    int maxLen;

    void maxPathSumRecursion(TreeNode* node, int& maxPathSumOnSingleSide)
    {
        if (node == NULL)
        {
            maxPathSumOnSingleSide = 0;
            return;
        }

        int leftChildMaxSumOnSingleSide;
        int rightChildMaxSumOnSingleSide;
        int leftSideMaxSum, rightSideMaxSum;

        maxPathSumRecursion(node->left, leftChildMaxSumOnSingleSide);
        maxPathSumRecursion(node->right, rightChildMaxSumOnSingleSide);

        if (leftChildMaxSumOnSingleSide < 0)
            leftSideMaxSum = node->val;
        else
            leftSideMaxSum = node->val + leftChildMaxSumOnSingleSide;

        if (rightChildMaxSumOnSingleSide < 0)
            rightSideMaxSum = node->val;
        else
            rightSideMaxSum = node->val + rightChildMaxSumOnSingleSide;

        if (leftSideMaxSum > this->maxLen)
            this->maxLen = leftSideMaxSum;

        if (rightSideMaxSum > this->maxLen)
            this->maxLen = rightSideMaxSum;

        if (leftSideMaxSum + rightSideMaxSum - node->val > this->maxLen)
            this->maxLen = leftSideMaxSum + rightSideMaxSum - node->val;

        if (leftSideMaxSum > rightSideMaxSum)
            maxPathSumOnSingleSide = leftSideMaxSum;
        else
            maxPathSumOnSingleSide = rightSideMaxSum;

        return;
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    return 0;
}

