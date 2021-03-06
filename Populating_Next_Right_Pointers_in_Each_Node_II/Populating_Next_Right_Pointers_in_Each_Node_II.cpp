// Populating_Next_Right_Pointers_in_Each_Node_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

//Definition for binary tree with next pointer.
typedef struct __TreeLinkNode {
    int val;
    __TreeLinkNode *left, *right, *next;
    __TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
}TreeLinkNode;

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return;

        root->next = NULL;

        TreeLinkNode* curLevelFirstNode = root;
        TreeLinkNode* nextLevelFirstNode = NULL;
        TreeLinkNode* curNode, *nextNode;

        while (curLevelFirstNode)
        {
            curNode = findNextNodeWithChildren(curLevelFirstNode);
            if (curNode == NULL)
                break;

            nextLevelFirstNode = curNode->left ? curNode->left : curNode->right;

            while (curNode) //curNode here must have at least one child
            {
                if (curNode->left)
                {
                    curNode->left->next = NULL;
                    if (curNode->right)
                    {
                        curNode->left->next = curNode->right;
                    }
                    else
                    {
                        nextNode = findNextNodeWithChildren(curNode->next);
                        if (nextNode == NULL)
                            break;
                        curNode->left->next = nextNode->left ? nextNode->left : nextNode->right;
                        curNode = nextNode;
                        continue;
                    }
                }

                nextNode = findNextNodeWithChildren(curNode->next);
                if (curNode->right)
                {
                    curNode->right->next = NULL;
                    if (nextNode == NULL)
                        break;

                    curNode->right->next = nextNode->left ? nextNode->left : nextNode->right;
                }

                curNode = nextNode;
            }

            curLevelFirstNode = nextLevelFirstNode;
            nextLevelFirstNode = NULL;
        }

        return;
    }

private:
    inline TreeLinkNode* findNextNodeWithChildren(TreeLinkNode* node)
    {
        if (node == NULL)
            return NULL;

        while (node && node->left == NULL && node->right == NULL)
            node = node->next;

        return node;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

