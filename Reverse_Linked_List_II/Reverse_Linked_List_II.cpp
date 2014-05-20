// Reverse_Linked_List_II.cpp : 定义控制台应用程序的入口点。
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
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (head == NULL)
            return NULL;

        if (head->next == NULL || m == n)
            return head;

        m--; n--;

        if (m == 0)
        {
            head = reverseList(head, n - m + 1);
            return head;
        }

        int c = 0;
        ListNode* curNode = head;
        ListNode* tail = NULL;
        while (c < m)
        {
            assert(curNode);
            tail = curNode;
            curNode = curNode->next;
            c++;            
        }

        curNode = reverseList(curNode, n - m + 1);
        tail->next = curNode;

        return head;
    }

private:
    inline ListNode* reverseList(ListNode* head, int count)
    {
        if (head == NULL || count == 1)
            return head;

        ListNode* curNode = head->next;
        ListNode* tail = head;
        ListNode* nextNode = NULL;
        tail->next = NULL;
        int m = 1;

        while (m < count)
        {
            assert(curNode);
            nextNode = curNode->next;
            curNode->next = head;
            head = curNode;
            m++;
            curNode = nextNode;
        }

        tail->next = curNode;
        return head;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

