// Symmetric_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <queue>

using namespace std;

typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == NULL)
            return true;

        TreeNode*   elem1 = NULL;
        TreeNode*   elem2 = NULL;
        queue<TreeNode*>    q1, q2, q3, q4;
        queue<TreeNode*>    *curQ1 = &q1, *curQ2 = &q2, *nextQ1 = &q3, *nextQ2 = &q4, *tempQ = NULL;
        curQ1->push(root);
        curQ2->push(root);

        while (!curQ1->empty())
        {
            while (!curQ1->empty())
            {
                if (curQ2->empty())
                    return false;

                elem1 = curQ1->front();
                elem2 = curQ2->front();
                curQ1->pop(); curQ2->pop();

                if (elem1->left)
                {
                    if (elem2->right == NULL || elem2->right->val != elem1->left->val)
                        return false;

                    nextQ1->push(elem1->left);
                    nextQ2->push(elem2->right);
                }
                else if (elem2->right)
                    return false;

                if (elem1->right)
                {
                    if (elem2->left == NULL || elem2->left->val != elem1->right->val)
                        return false;

                    nextQ1->push(elem1->right);
                    nextQ2->push(elem2->left);
                }
                else if (elem2->left)
                    return false;
            }

            if (!curQ2->empty())
                return false;

            if (nextQ1->size() != nextQ2->size())
                return false;

            tempQ = nextQ1;
            nextQ1 = curQ1;
            curQ1 = tempQ;

            tempQ = nextQ2;
            nextQ2 = curQ2;
            curQ2 = tempQ;
        }

        if (!curQ2->empty())
            return false;

        return true;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

