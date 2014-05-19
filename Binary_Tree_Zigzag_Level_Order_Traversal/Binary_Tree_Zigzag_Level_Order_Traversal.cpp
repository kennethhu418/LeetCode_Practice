// Binary_Tree_Zigzag_Level_Order_Traversal.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;


typedef struct _TreeNode {
    int val;
    _TreeNode *left;
    _TreeNode *right;
    _TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> resultA;
        vector<int> curLevelResult;

        if (root == NULL)
            return resultA;

        char fromLeftTrace = 0;
        int     curPos;
        queue<TreeNode*>    q1, q2;
        queue<TreeNode*>*  curQ = &q1, *nextQ = &q2, *tempQ;
        curQ->push(root);

        while (!curQ->empty())
        {
            fromLeftTrace = 1 - fromLeftTrace;
            curLevelResult.resize(curQ->size());
            
            if (fromLeftTrace)
                curPos = 0;
            else
                curPos = curQ->size() - 1;

            while (!curQ->empty())
            {
                root = curQ->front();
                curQ->pop();

                curLevelResult[curPos] = root->val;
                if (fromLeftTrace)
                    curPos++;
                else
                    curPos--;

                if (root->left)
                    nextQ->push(root->left);
                if (root->right)
                    nextQ->push(root->right);               
            }

            resultA.push_back(curLevelResult);
            curLevelResult.clear();

            tempQ = nextQ;
            nextQ = curQ;
            curQ = tempQ;
        }

        return resultA;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

