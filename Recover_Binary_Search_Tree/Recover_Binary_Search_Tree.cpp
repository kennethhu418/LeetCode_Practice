// Recover_Binary_Search_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

#define DEFAULT_MIN_VAL     (0 - 0x7FFFFFFF)
#define DEFAULT_MAX_VAL     0x7FFFFFFF

typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {

public:
    void recoverTree(TreeNode *root) {
        if (root == NULL)
            return;

        swappedLargeOne = swappedSmallerOne = curLargestNode = NULL;

        findSwappedElements(root);

        swappedLargeOne->val ^= swappedSmallerOne->val;
        swappedSmallerOne->val ^= swappedLargeOne->val;
        swappedLargeOne->val ^= swappedSmallerOne->val;
    }

private:
    TreeNode *swappedLargeOne, *swappedSmallerOne, *curLargestNode;

    void findSwappedElements(TreeNode *root)
    {
        if (root == NULL)
            return;

        findSwappedElements(root->left);

        if (curLargestNode && curLargestNode->val > root->val)
        {
            if (swappedLargeOne == NULL)
            {
                swappedLargeOne = curLargestNode;
                swappedSmallerOne = root;
            }
            else
            {
                swappedSmallerOne = root;
            }
        }

        curLargestNode = root;

        findSwappedElements(root->right);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    TreeNode node1 = { 4 };
    TreeNode node2 = { 3 };
    TreeNode node3 = { 2 };
    TreeNode node4 = { 1 };

    node1.right = &node2;
    node2.left = &node3;
    node2.right = &node4;

    Solution s;
    s.recoverTree(&node1);

	return 0;
}

