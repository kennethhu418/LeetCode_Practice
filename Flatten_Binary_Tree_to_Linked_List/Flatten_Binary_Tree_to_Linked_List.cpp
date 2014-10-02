// Flatten_Binary_Tree_to_Linked_List.cpp : 定义控制台应用程序的入口点。
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
    void flatten(TreeNode *root) {
        if (root == NULL || (root->left == NULL && root->right == NULL))
            return;

        latestVisitedNode = NULL;
        flattenTree(root);
    }

private:
    TreeNode* latestVisitedNode;

    void flattenTree(TreeNode* node)
    {
        TreeNode* leftNode = node->left;
        TreeNode* rightNode = node->right;

        if (latestVisitedNode)
            latestVisitedNode->right = node;

        node->left = NULL;
        node->right = NULL;
        latestVisitedNode = node;

        if (leftNode)
            flattenTree(leftNode);
        if (rightNode)
            flattenTree(rightNode);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	TreeNode node1(1);
	TreeNode node2(2);
	node1.left = &node2;

	Solution solution;
	solution.flatten(&node1);

	return 0;
}

