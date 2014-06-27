// Recover_Binary_Search_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <stack>

using std::stack;

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

        target1 = NULL;
        target2 = NULL;
        lastestVisitedNode = NULL;

        InorderTraversalWithCheck(root);

        assert(target1 && target2);
        target1->val ^= target2->val;
        target2->val ^= target1->val;
        target1->val ^= target2->val;
    }

private:
    TreeNode* target1;
    TreeNode* target2;
    TreeNode* lastestVisitedNode;

    void InorderTraversalWithCheck(TreeNode* root)
    {
        if (root == NULL)
            return;

        InorderTraversalWithCheck(root->left);
        if (lastestVisitedNode != NULL)
        {
            if (lastestVisitedNode->val > root->val)
            {
                if (target1 == NULL)
                    target1 = lastestVisitedNode;
                target2 = root;
            }
        }

        lastestVisitedNode = root;

        InorderTraversalWithCheck(root->right);
    }
};

class Solution_NonRecursive{
public:
    void recoverTree(TreeNode *root) {
        if (root == NULL)
            return;
        if (root->left == NULL && root->right == NULL)
            return;

        TreeNode* curNode = getSmallestNode(root); //get the smallest node based on structure
        TreeNode* nextNode = NULL;
        TreeNode* firstNode = NULL, *secondNode = NULL;

        while (curNode)
        {
            nextNode = getNextLargerNode(curNode); //get the next larger node based on structure
            if (nextNode == NULL)
                break;

            if (nextNode->val < curNode->val)
            {
                firstNode = curNode;
                break;
            }

            curNode = nextNode;
        }

        ClearAuxBuffer(); //clear stack

        curNode = getLargestNode(root); //get the largest node based on structure
        nextNode = NULL;
        while (curNode)
        {
            nextNode = getNextSmallerNode(curNode); //get the next smaller node based on structure
            if (nextNode == NULL)
                break;

            if (nextNode->val > curNode->val)
            {
                secondNode = curNode;
                break;
            }

            curNode = nextNode;
        }

        ClearAuxBuffer(); //clear stack

        assert(firstNode && secondNode);

        firstNode->val ^= secondNode->val;
        secondNode->val ^= firstNode->val;
        firstNode->val ^= secondNode->val;
    }

private:
    stack<TreeNode*>    parentStack;

    TreeNode* getSmallestNode(TreeNode* root)
    {
        if (root == NULL)
            return NULL;

        while (root->left)
        {
            parentStack.push(root);
            root = root->left;
        }

        return root;
    }

    TreeNode* getLargestNode(TreeNode* root)
    {
        if (root == NULL)
            return NULL;

        while (root->right)
        {
            parentStack.push(root);
            root = root->right;
        }

        return root;
    }

    inline TreeNode* getNextLargerNode(TreeNode* node)
    {
        if (node == NULL)
            return NULL;

        if (node->right)
        {
            parentStack.push(node);
            node = node->right;

            while (node->left)
            {
                parentStack.push(node);
                node = node->left;
            }

            return node;
        }

        if (parentStack.empty())
            return NULL;

        TreeNode* parent = parentStack.top();
        if (parent->left == node)
        {
            parentStack.pop();
            return parent;
        }

        while (!parentStack.empty())
        {
            parentStack.pop();
            if (parentStack.empty())
                return NULL;

            if (parentStack.top()->left == parent)
            {
                parent = parentStack.top();
                parentStack.pop();
                return parent;
            }

            parent = parentStack.top();
        }

        return NULL;
    }

    inline TreeNode* getNextSmallerNode(TreeNode* node)
    {
        if (node == NULL)
            return NULL;

        if (node->left)
        {
            parentStack.push(node);
            node = node->left;

            while (node->right)
            {
                parentStack.push(node);
                node = node->right;
            }

            return node;
        }

        if (parentStack.empty())
            return NULL;

        TreeNode* parent = parentStack.top();
        if (parent->right == node)
        {
            parentStack.pop();
            return parent;
        }

        while (!parentStack.empty())
        {
            parentStack.pop();
            if (parentStack.empty())
                return NULL;

            if (parentStack.top()->right == parent)
            {
                parent = parentStack.top();
                parentStack.pop();
                return parent;
            }

            parent = parentStack.top();
        }

        return NULL;
    }

    void ClearAuxBuffer()
    {
        while (!parentStack.empty())
            parentStack.pop();
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

