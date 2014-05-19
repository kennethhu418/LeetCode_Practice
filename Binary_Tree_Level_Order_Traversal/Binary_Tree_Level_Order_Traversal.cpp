// Binary_Tree_Level_Order_Traversal.cpp : 定义控制台应用程序的入口点。
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
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> >    result;
        vector<int> curLevelResult;

        if (root == NULL)
            return result;

        queue<TreeNode*> queue1, queue2;
        queue<TreeNode*>*   curQ = &queue1, *nextQ = &queue2, *tempQ = NULL;
        curQ->push(root);
        int curLevel = 0;

        while (!curQ->empty())
        {
            result.push_back(curLevelResult);
                        
            while (!curQ->empty())
            {
                root = curQ->front();
                curQ->pop();

                result[curLevel].push_back(root->val);
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
};

int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> v(13);
    v[12] = 0;
    v[11] = 1;
    v[10] = 2;

    return 0;
}

