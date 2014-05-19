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
        assert(swappedNode1 && swappedNode2 && swappedNode1->val > swappedNode2->val);

        swappedNode1->val ^= swappedNode2->val;
        swappedNode2->val ^= swappedNode1->val;
        swappedNode1->val ^= swappedNode2->val;
    }

private:
    void findSwappedElements(TreeNode* node, int curSmallerValue, int curLargerValue,
        int &minVal, int &maxVal,
        TreeNode* &foundSwappedNodeLargeOne, TreeNode* &foundSwappedNodeSmallOne)
    {
        if (node == NULL)
            return;

        minVal = maxVal = node->val;
        int childMinVal, childMaxVal;

        int curNodeSmallerVal = curSmallerValue, curNodeLargerVal = curLargerValue;

        TreeNode* foundSwappedNodeInLeftChildLargeOne = NULL, *foundSwappedNodeInLeftChildSmallOne = NULL;
        TreeNode* foundSwappedNodeInRightChildLargeOne = NULL, *foundSwappedNodeInRightChildSmallOne = NULL;

        if (node->left)
        {
            findSwappedElements(node->left, curSmallerValue, node->val, childMinVal, childMaxVal,
                foundSwappedNodeInLeftChildLargeOne, foundSwappedNodeInLeftChildSmallOne);

            minVal = childMinVal;
            curNodeSmallerVal = childMaxVal;
        }

        if (node->right)
        {
            findSwappedElements(node->right, node->val, curLargerValue, childMinVal, childMaxVal,
                foundSwappedNodeInRightChildLargeOne, foundSwappedNodeInRightChildSmallOne);

            maxVal = childMaxVal;
            curNodeLargerVal = childMinVal;
        }

        foundSwappedNodeLargeOne = foundSwappedNodeInLeftChildLargeOne ? foundSwappedNodeInLeftChildLargeOne : foundSwappedNodeInRightChildLargeOne;
        foundSwappedNodeSmallOne = foundSwappedNodeInRightChildSmallOne ? foundSwappedNodeInRightChildSmallOne : foundSwappedNodeInLeftChildSmallOne;

        if (!foundSwappedNodeInLeftChildLargeOne && node->val > curNodeSmallerVal && node->val > curNodeLargerVal)
            foundSwappedNodeLargeOne = node;

        if (!foundSwappedNodeInRightChildSmallOne && node->val < curNodeSmallerVal && node->val < curNodeLargerVal)
            foundSwappedNodeSmallOne = node;

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

