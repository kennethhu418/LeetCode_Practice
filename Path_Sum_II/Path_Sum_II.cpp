// Path_Sum_II.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;


typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > result;
        vector<int> traversePath;
        int pathSumVal = 0;

        pathSum(root, sum, pathSumVal, result, traversePath);

        return result;
    }

private:
    void pathSum(TreeNode* curNode, const int& sum, int& curSum,
        vector<vector<int> >& result, vector<int>& curPath)
    {
        if (curNode == NULL)
            return;

        if (curNode->left == NULL && curNode->right == NULL)
        {
            if (curNode->val + curSum == sum)
            {
                curPath.push_back(curNode->val);
                result.push_back(curPath);
                curPath.pop_back();
            }

            return;
        }

        curSum += curNode->val;
        curPath.push_back(curNode->val);

        if (curNode->left)
            pathSum(curNode->left, sum, curSum, result, curPath);

        if (curNode->right)
            pathSum(curNode->right, sum, curSum, result, curPath);

        curSum -= curNode->val;
        curPath.pop_back();
        return;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

