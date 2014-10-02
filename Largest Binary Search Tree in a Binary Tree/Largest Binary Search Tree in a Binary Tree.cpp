// Largest Binary Search Tree in a Binary Tree.cpp : 定义控制台应用程序的入口点。
//

//Given a binary tree, find the largest Binary Search Tree(BST), where largest means BST with largest number of nodes in it.
//The largest BST may or may not include all of its descendants.


#include <iostream>
using namespace std;

#define MIN_VAL 0x80000000
#define MAX_VAL 0x7fffffff

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode *getLargestBST(TreeNode *root, int &maxSize){
        if (root == NULL)	return NULL;
        largestRoot = root;
        largestSize = 1;
        searchLargestBST(root, MIN_VAL, MAX_VAL);
        maxSize = largestSize;
        return largestRoot;
    }

private:
    int largestSize;
    TreeNode *largestRoot;

    int searchLargestBST(TreeNode *root, int min_val, int max_val)
    {
        if (root == NULL) return 0;

        //First check with no limitation
        int curSize = 1;
        curSize += searchLargestBST(root->left, MIN_VAL, root->val);
        curSize += searchLargestBST(root->right, root->val, MAX_VAL);
        if (curSize > largestSize){
            largestSize = curSize;
            largestRoot = root;
        }

        //Now check with limitation
        curSize = 0;
        if (root->val >= min_val && root->val <= max_val){
            curSize = 1;
            curSize += searchLargestBST(root->left, min_val, root->val);
            curSize += searchLargestBST(root->right, root->val, max_val);
        }
        return curSize;
    }
};

int main()
{
    TreeNode node19(19);
    TreeNode node20(20);
    TreeNode node45(45);
    TreeNode node11(11);
    TreeNode node12(12);
    TreeNode node35(35);
    TreeNode node44(44);
    TreeNode node13(13);
    TreeNode node8(8);
    TreeNode node21(21);

    node19.left = &node20;
    node19.right = &node45;
    node20.left = &node11;
    node20.right = &node12;
    node45.left = &node35;
    node45.right = &node44;
    node11.left = &node13;
    node12.left = &node8;
    node12.right = &node21;

    Solution so;
    int bstSize = 0;
    TreeNode* bstRoot = so.getLargestBST(&node19, bstSize);

    cout << bstRoot->val << "  " << bstSize << endl;
    return 0;
}