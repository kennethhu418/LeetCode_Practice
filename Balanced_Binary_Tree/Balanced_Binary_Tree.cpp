// Balanced_Binary_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
#include <assert.h>

using namespace std;


typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

typedef struct __StackElem
{
    TreeNode* node;
    int leftHeight;
    int rightHeight;
    char opStep; //0: the entry 1: visiting left  2: visiting right
    bool childBalanced;
}StackElem;

class Solution {
public:
    bool isBalanced(TreeNode *root) {
        int height = 0;
        
        //Recursive Result
        //return isBalancedWithCalcHeight_Recursive(root, height);

        //Non-recursive Result
        return isBalancedWithCalcHeight_NonRecursive(root);
    }

private:
    bool isBalancedWithCalcHeight_NonRecursive(TreeNode* root)
    {
        if (root == NULL)
            return true;

        StackElem e = {root, 0, 0, 0, true};
        StackElem e1;
        stack<StackElem> stackA;
        stackA.push(e);
        int retHeight;

        while (!stackA.empty())
        {
            e = stackA.top();
            stackA.pop();

            if (e.opStep == 0)
            {
                if (e.node == NULL)
                {
                    if (!stackA.empty())
                        stackA.top().childBalanced = true;
                    continue;
                }

                if (e.node->left)
                {
                    e.opStep = 1;

                    e1.node = e.node->left;
                    e1.childBalanced = true;
                    e1.leftHeight = e1.rightHeight = 0;
                    e1.opStep = 0;

                    stackA.push(e);
                    stackA.push(e1);
                    continue;
                }

                e.opStep = 1;
                stackA.push(e);
                continue;
            }
            else if (e.opStep == 1)  //just visited left child
            {
                if (e.childBalanced == false)
                {
                    if (!stackA.empty())
                        stackA.top().childBalanced = false;
                    continue;
                }

                if (e.node->right)
                {
                    e.opStep = 2;

                    e1.node = e.node->right;
                    e1.childBalanced = true;
                    e1.leftHeight = e1.rightHeight = 0;
                    e1.opStep = 0;

                    stackA.push(e);
                    stackA.push(e1);
                    continue;
                }

                e.opStep = 2;
                stackA.push(e);
                continue;
            }
            else if (e.opStep == 2) //just visited right child
            {
                if (e.childBalanced == false)
                {
                    if (!stackA.empty())
                        stackA.top().childBalanced = false;
                    continue;
                }

                if (e.leftHeight == e.rightHeight || e.leftHeight - e.rightHeight == 1
                    || e.leftHeight - e.rightHeight == -1)
                {
                    if (!stackA.empty())
                    {
                        stackA.top().childBalanced = true;
                        retHeight = 1 + (e.leftHeight > e.rightHeight ? e.leftHeight : e.rightHeight);
                        if (stackA.top().opStep == 1)
                            stackA.top().leftHeight = retHeight;
                        else
                        {
                            assert(stackA.top().opStep == 2);
                            stackA.top().rightHeight = retHeight;
                        }
                    }
                    continue;
                }

                if (!stackA.empty())
                {
                    stackA.top().childBalanced = false;                    
                }

                continue;
            } //end if(opStep == 0, 1, 2)

            assert(0); //should never be such an invalid opStep
        }

        if (e.childBalanced == false)
            return false;

        if (e.leftHeight == e.rightHeight || e.leftHeight - e.rightHeight == 1
            || e.leftHeight - e.rightHeight == -1)
            return true;

        return false;
    }


    bool isBalancedWithCalcHeight_Recursive(TreeNode* root, int& height)
    {
        if (root == NULL)
        {
            height = 0;
            return true;
        }

        int leftHeight = 0, rightHeight = 0;

        if (root->left && !isBalancedWithCalcHeight_Recursive(root->left, leftHeight))
            return false;

        if (root->right && !isBalancedWithCalcHeight_Recursive(root->right, rightHeight))
            return false;

        if (leftHeight == rightHeight || leftHeight - rightHeight == 1
            || leftHeight - rightHeight == -1)
        {
            height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
            return true;
        }

        return false;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    TreeNode node1 = { 1 };
    TreeNode node2 = { 2 };
    TreeNode node3 = { 3 };
    node1.right = &node2;
    node1.left = &node3;

    Solution solution;
    bool ret = solution.isBalanced(&node1);

	return 0;
}

