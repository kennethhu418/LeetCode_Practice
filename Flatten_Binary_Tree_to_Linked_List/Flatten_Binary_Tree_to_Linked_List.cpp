// Flatten_Binary_Tree_to_Linked_List.cpp : 定义控制台应用程序的入口点。
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
	void flatten(TreeNode *root) {
		TreeNode* link_head = NULL, *link_tail = NULL;

		flatten_recursive(root, link_head, link_tail);
	}

private:
	void flatten_recursive(TreeNode* root, TreeNode* &link_head, TreeNode* &link_tail)
	{
		if (root == NULL)
		{
			link_head = link_tail = NULL;
			return;
		}

		link_head = root;

		TreeNode* left_childLink_head = NULL, *left_childLink_tail = NULL;
		TreeNode* right_childLink_head = NULL, *right_childLink_tail = NULL;
		
		flatten_recursive(root->left, left_childLink_head, left_childLink_tail);
		flatten_recursive(root->right, right_childLink_head, right_childLink_tail);
		root->left = NULL;
		root->right = NULL;

		if (left_childLink_head != NULL)
		{
			root->right = left_childLink_head;
			left_childLink_head->left = NULL;
			assert(left_childLink_tail);

			left_childLink_tail->right = right_childLink_head;
			if (right_childLink_head != NULL)
			{
				right_childLink_head->left = NULL;
				assert(right_childLink_tail);
				right_childLink_tail->right = NULL;
				link_tail = right_childLink_tail;
			}
			else
			{
				link_tail = left_childLink_tail;
			}

			return;
		}

		root->right = right_childLink_head;
		if (right_childLink_head)
		{
			right_childLink_head->left = NULL;
			assert(right_childLink_tail);
			right_childLink_tail->right = NULL;
			link_tail = right_childLink_tail;
		}
		else
			link_tail = root;

		return;
	}
};

void OutputResult(TreeNode* root)
{
	while (root)
	{
		printf("%d ", root->val);
		root = root->right;
	}

	printf("\n\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	TreeNode node1(1);
	TreeNode node2(2);
	node1.left = &node2;

	Solution solution;
	solution.flatten(&node1);

	OutputResult(&node1);
	return 0;
}

