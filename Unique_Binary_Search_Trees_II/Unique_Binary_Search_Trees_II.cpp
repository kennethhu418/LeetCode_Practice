// Unique_Binary_Search_Trees_II.cpp : 定义控制台应用程序的入口点。
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

typedef struct __QElem
{
    TreeNode*   node;
    TreeNode*   parent;
    int                  isLeftChild;
}QElem;

class Solution_Recursive {
public:
    vector<TreeNode *> generateTrees(int n) {
        return generateTrees(1, n);
    }

private:
    vector<TreeNode* > generateTrees(int start, int end) {
        vector<TreeNode *>  result;

        if (start > end)
        {
            result.push_back(NULL);
            return result;
        }

        for (int curRoot = start; curRoot <= end; curRoot++)
        {
            vector<TreeNode*>   leftTrees = generateTrees(start, curRoot - 1);
            vector<TreeNode*>   rightTrees = generateTrees(curRoot + 1, end);

            for (int i = 0; i < leftTrees.size(); i++)
            {
                for (int j = 0; j < rightTrees.size(); j++)
                {
                    TreeNode*   root = new TreeNode(curRoot);
                    root->left = leftTrees[i];
                    root->right = rightTrees[j];
                    result.push_back(root);
                }
            }
        }

        return result;
    };
};

class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        vector<TreeNode*>   result;
        result.push_back(NULL);

        if (n == 0)
            return result;

        vector<vector<TreeNode*>> resultA;
        resultA.push_back(result);

        for (int curNodeNum = 1; curNodeNum <= n; curNodeNum++)
        {
            result.clear();
            for (int k = 1; k <= curNodeNum; k++)
                CombineResults(k, resultA[k - 1], resultA[curNodeNum - k], result);
            
            if (curNodeNum != n)
                resultA.push_back(result);
        }

        DestroyTreesInArray(resultA);
        return result;
    }

private:
    void CombineResults(int rootVal, vector<TreeNode*> & leftTrees, vector<TreeNode*> &rightTrees, vector<TreeNode*> &resultArray)
    {
        TreeNode* root;
        for (int i = 0; i < leftTrees.size(); i++)
        {
            for (int j = 0; j < rightTrees.size(); j++)
            {
                root = new TreeNode(rootVal);
                root->left = CloneTreeWithIncrement(leftTrees[i], 0);
                root->right = CloneTreeWithIncrement(rightTrees[j], rootVal);
                resultArray.push_back(root);
            }
        }
    }

    TreeNode* CloneTreeWithIncrement(TreeNode* root, int incrementVal)
    {
        if (root == NULL)
            return NULL;

        QElem   e = {root, NULL, false}, newE;
        queue<QElem>    queueA;
        TreeNode*   newRoot = NULL, *curNewNode;
        queueA.push(e);

        while (!queueA.empty())
        {
            e = queueA.front();
            queueA.pop();

            curNewNode = new TreeNode(incrementVal + e.node->val);
            if (newRoot == NULL)
                newRoot = curNewNode;

            if (e.parent)
            {
                if (e.isLeftChild)
                    e.parent->left = curNewNode;
                else
                    e.parent->right = curNewNode;
            }
                
            if (e.node->left)
            {
                newE.node = e.node->left;
                newE.parent = curNewNode;
                newE.isLeftChild = true;
                queueA.push(newE);
            }

            if (e.node->right)
            {
                newE.node = e.node->right;
                newE.parent = curNewNode;
                newE.isLeftChild = false;
                queueA.push(newE);
            }            
        }

        return newRoot;        
    }

    void DestroyTreesInArray(vector<vector<TreeNode*>> resultArray)
    {
        int size = resultArray.size();

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < resultArray[i].size(); j++)
                DestroyTree(resultArray[i][j]);
        }
    }

    void DestroyTree(TreeNode* root)
    {
        if (root == NULL)
            return;

        queue<TreeNode*>    queueA;
        TreeNode*   curNode;
        queueA.push(root);

        while (!queueA.empty())
        {
            curNode = queueA.front();
            queueA.pop();

            if (curNode->left)
                queueA.push(curNode->left);

            if (curNode->right)
                queueA.push(curNode->right);

            delete curNode;
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}