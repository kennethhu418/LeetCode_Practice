// Insertion_Sort_List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



typedef struct _ListNode {
    int val;
    _ListNode *next;
    _ListNode(int x) : val(x), next(NULL) {}
}ListNode;

class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if(head == NULL || head->next == NULL)
            return head;

        ListNode* curNode = head->next, *tailNode = head, *nextNode = NULL;
        tailNode->next = NULL;

        while(curNode)
        {
            nextNode = curNode->next;
            head = InsertNode(head, tailNode, curNode);
            curNode = nextNode;
        }

        return head;        
    }

private:
    ListNode* InsertNode(ListNode* &head, ListNode* &tail, ListNode* tNode)
    {
        if (tNode == NULL)
        {
            return head;
        }
        if (head == NULL)
        {
            head = tail = tNode;
            tNode->next = NULL;
            return head;
        }

        ListNode* prevNode = NULL, *curNode = head;

        while(curNode)
        {
            if (tNode->val >= curNode->val)
            {
                prevNode = curNode;
                curNode = prevNode->next;
                continue;
            }

            if (prevNode == NULL)
            {
                tNode->next = head;
                head = tNode;
                return head;
            }

            prevNode->next = tNode;
            tNode->next = curNode;
            return head;
        }

        tail->next = tNode;
        tNode->next = NULL;
        tail = tNode;
        return head;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

