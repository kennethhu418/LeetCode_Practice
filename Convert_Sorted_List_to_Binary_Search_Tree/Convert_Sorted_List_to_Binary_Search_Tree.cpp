// Convert_Sorted_List_to_Binary_Search_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
#include <assert.h>

using namespace std;

typedef struct __ListNode {
    int val;
    __ListNode *next;
    __ListNode(int x) : val(x), next(NULL) {}
}ListNode;


typedef struct __TreeNode {
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        int listLen = GetListLength(head);
        if (listLen == 0)
            return NULL;

        ListNode* tail = NULL;
        return sortedListToBST(head, listLen, tail);
    }

private:
    inline int GetListLength(ListNode* head)
    {
        int len = 0;
        while (head)
        {
            len++;
            head = head->next;
        }

        return len;
    }

    TreeNode* sortedListToBST(ListNode* head, int length, ListNode* &listTail)
    {
        TreeNode* root = NULL;
        if (length == 0)
        {
            listTail = NULL;
            return root;
        }

        assert(head);

        if (length == 1)
        {
            root = new TreeNode(head->val);
            listTail = head;
            return root;
        }

        int leftNum = length / 2;
        int rightNum = length - leftNum - 1;

        ListNode* tail = NULL;
        TreeNode* subTree = sortedListToBST(head, leftNum, tail);
        assert(subTree && tail && tail->next);

        ListNode* rootListNode = tail->next;
        root = new TreeNode(rootListNode->val);
        root->left = subTree;
        listTail = rootListNode;

        if (rightNum)
        {
            assert(tail->next->next);
            tail = NULL;
            subTree = sortedListToBST(rootListNode->next, rightNum, tail);
            root->right = subTree;
            listTail = tail;
        }

        return root;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    ListNode node1(3);
    ListNode node2(5);
    ListNode node3(8);

    node1.next = &node2;
    node2.next = &node3;

    Solution s;
    s.sortedListToBST(&node1);


	return 0;
}