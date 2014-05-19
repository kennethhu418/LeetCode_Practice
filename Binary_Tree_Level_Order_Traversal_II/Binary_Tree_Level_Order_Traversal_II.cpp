// Binary_Tree_Level_Order_Traversal_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        int levelNumber = GetTreeHeight(root);
        vector<vector<int> >    result(levelNumber);
        if (levelNumber == 0)
            return result;

        queue<TreeNode*> queue1, queue2;
        queue<TreeNode*>*   curQ = &queue1, *nextQ = &queue2, *tempQ = NULL;
        curQ->push(root);
        int curLevel = 0;
        int curPosInResult;

        while (!curQ->empty())
        {
            curPosInResult = levelNumber - 1 - curLevel;

            while (!curQ->empty())
            {
                root = curQ->front();
                curQ->pop();

                result[curPosInResult].push_back(root->val);
                if (root->left)
                    nextQ->push(root->left);
                if (root->right)
                    nextQ->push(root->right);
            }

            curLevel++;
            tempQ = curQ;
            curQ = nextQ;
            nextQ = tempQ;
        }

        return result;
    }

private:
    int GetTreeHeight(TreeNode* root)
    {
        int height = 0;

        if (root == NULL)
            return height;

        int left_height = 0, right_height = 0;
        left_height     = GetTreeHeight(root->left);
        right_height    = GetTreeHeight(root->right);
        height = 1 + (left_height > right_height ? left_height : right_height);
        return height;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> v(13);
    v[12] = 0;
    v[11] = 1;
    v[10] = 2;

	return 0;
}

