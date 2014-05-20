// Binary_Tree_Inorder_Traversal.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
#include <vector>

using namespace std;

typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

typedef struct _Elem
{
    TreeNode*   node;
    int step;
}Elem;

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> resultA;
        if (root == NULL)
            return resultA;

        stack<Elem> stackA;
        Elem e = {root, 0};
        stackA.push(e);

        while (!stackA.empty())
        {
            e = stackA.top();
            stackA.pop();

            if (e.step == 0)
            {
                e.step = 1;
                stackA.push(e);

                if (e.node->left)
                {
                    e.node = e.node->left;
                    e.step = 0;
                    stackA.push(e);
                    continue;
                }
            }
            else if (e.step == 1)
            {
                resultA.push_back(e.node->val);
                if (e.node->right)
                {
                    e.node = e.node->right;
                    e.step = 0;
                    stackA.push(e);
                }
            }
        }

        return resultA;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

