// Reorder_List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>


typedef struct __ListNode {
    int val;
    __ListNode *next;
    __ListNode(int x) : val(x), next(NULL) {}
}ListNode;

class Solution {
public:
    void reorderList(ListNode *head) {
        if (head == NULL || head->next == NULL || head->next->next == NULL)
        {
            return;
        }

        int size = GetSize(head);
        ListNode* splitNode = GetNodeByIndex(head, (size/2 - 1));
        assert(splitNode);

        ListNode* secondHalf = splitNode->next;
        splitNode->next = NULL;
        assert(secondHalf);

        secondHalf = RevertList(secondHalf);

        head = MergeTwoLists(head, secondHalf);
        return;       
    }

private:
    int GetSize(ListNode* root)
    {
        int size = 0;
        while(root)
        {
            size++;
            root = root->next;
        }

        return size;
    }

    ListNode* GetNodeByIndex(ListNode* root, int t)
    {
        int curIndex = 0;
        while(root)
        {
            if (curIndex == t)
            {
                return root;
            }
            curIndex++;
            root = root->next;
        }

        return NULL;
    }

    ListNode* RevertList(ListNode* root)
    {
        if (root == NULL || root->next == NULL)
        {
            return root;
        }

        ListNode* curNode = root->next, *nextNode = NULL;
        root->next = NULL;

        while(curNode)
        {
            nextNode = curNode->next;

            curNode->next = root;
            root = curNode;
            curNode = nextNode;
        }

        return root;
    }

    ListNode* MergeTwoLists(ListNode* root1, ListNode* root2)
    {
        if (root1 == NULL)
        {
            return root2;
        }
        else if (root2 == NULL)
        {
            return root1;
        }

        ListNode* head = NULL, *tail = NULL;

        while(root1 && root2)
        {
            if (head == NULL)
            {
                head = tail = root1;
            }
            else
            {
                tail->next = root1;
                tail = root1;
            }

            tail->next = root2;
            tail = root2;

            root1 = root1->next;
            root2 = root2->next;
        }

        if (root1 == NULL)
            tail->next = root2;
        else
            tail->next = root1;

        return head;
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

