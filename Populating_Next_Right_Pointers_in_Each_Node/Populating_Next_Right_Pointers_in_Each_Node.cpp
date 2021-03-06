// Populating_Next_Right_Pointers_in_Each_Node.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

 //Definition for binary tree with next pointer.
 typedef struct __TreeLinkNode {
      int val;
      __TreeLinkNode *left, *right, *next;
      __TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 }TreeLinkNode;

class Solution {
public:
    void connect(TreeLinkNode *root) {        
        if (root)
            root->next = NULL;

        TreeLinkNode* curLevelFirstNode = root;
        TreeLinkNode* nextLevelFirstNode = NULL;
        TreeLinkNode* curNode;

        while (curLevelFirstNode)
        {            
            if (curLevelFirstNode->left == NULL)
                break;

            nextLevelFirstNode = curLevelFirstNode->left;
            curNode = curLevelFirstNode;

            while (curNode)
            {
                if (curNode->left == NULL)
                    break;

                curNode->left->next = curNode->right;
                assert(curNode->right);

                if (curNode->next)
                    curNode->right->next = curNode->next->left;
                else
                    curNode->right->next = NULL;

                curNode = curNode->next;
            }

            curLevelFirstNode = nextLevelFirstNode;
            nextLevelFirstNode = NULL;
        }

        return;        
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

