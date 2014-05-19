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

        int smallerValue = DEFAULT_MIN_VAL, largerValue = DEFAULT_MAX_VAL;
        int minVal, maxVal;
        TreeNode* swappedNode1 = NULL, *swappedNode2 = NULL;

        findSwappedElements(root, smallerValue, largerValue, minVal, maxVal, swappedNode1, swappedNode2);
        assert(swappedNode1 && swappedNode2);

        swappedNode1->val ^= swappedNode2->val;
        swappedNode2->val ^= swappedNode1->val;
        swappedNode1->val ^= swappedNode2->val;
    }

private:
    void findSwappedElements(TreeNode* node, int curSmallerValue, int curLargerValue,
        int &minVal, int &maxVal,
        TreeNode* &foundSwappedNode1, TreeNode* &foundSwappedNode2)
    {
        if (node == NULL)
            return;

        minVal = maxVal = node->val;
        int childMinVal, childMaxVal;

        int curNodeSmallerVal = curSmallerValue, curNodeLargerVal = curLargerValue;

        if (node->left)
        {
            findSwappedElements(node->left, curSmallerValue, node->val, childMinVal, childMaxVal, foundSwappedNode1, foundSwappedNode2);
            if (foundSwappedNode1 != NULL && foundSwappedNode2 != NULL)
                return;
            minVal = childMinVal;
            curNodeSmallerVal = childMaxVal;
        }

        if (node->right)
        {
            findSwappedElements(node->right, node->val, curLargerValue, childMinVal, childMaxVal, foundSwappedNode1, foundSwappedNode2);
            if (foundSwappedNode1 != NULL && foundSwappedNode2 != NULL)
                return;
            maxVal = childMaxVal;
            curNodeLargerVal = childMinVal;
        }

        if (node->val > curNodeSmallerVal && node->val > curNodeLargerVal)
        {
            if (foundSwappedNode1 == NULL)
                foundSwappedNode1 = node;
            else if (foundSwappedNode2 == NULL)
                foundSwappedNode2 = node;
            else
                assert(0);
        }

        if (node->val < curNodeSmallerVal && node->val < curNodeLargerVal)
        {
            if (foundSwappedNode1 == NULL)
                foundSwappedNode1 = node;
            else if (foundSwappedNode2 == NULL)
                foundSwappedNode2 = node;
            else
                assert(0);
        }

        return;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

