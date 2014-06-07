// Swap_Nodes_in_Pairs.cpp : 定义控制台应用程序的入口点。
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
    ListNode* swapPairs(ListNode *head)
    {
        return reverseKGroup(head, 2);
    }

private:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if (head == NULL || k < 2)
            return head;

        ListNode* curStart = head, *curEnd = NULL, *tail = NULL;
        int movedOnNodes = 0;
        curEnd = moveOnKNodes(curStart, k, movedOnNodes);
        if (movedOnNodes < k)
            return head;

        head = reverseList(curStart, curEnd);
        tail = curStart;
        curStart = tail->next;

        while (curStart)
        {
            curEnd = moveOnKNodes(curStart, k, movedOnNodes);
            if (movedOnNodes < k)
                break;

            tail->next = reverseList(curStart, curEnd);
            tail = curStart;
            curStart = tail->next;
        }

        return head;
    }

    inline ListNode* moveOnKNodes(ListNode* head, int k, int &actualNodes)
    {
        assert(head);
        actualNodes = 1;

        while (actualNodes < k)
        {
            if (head->next == NULL)
                break;
            head = head->next;
            actualNodes++;
        }

        return head;
    }

    inline ListNode* reverseList(ListNode* first, ListNode* end)
    {
        assert(first && end);
        if (first == end)
            return first;

        ListNode* head = first, *tail = first, *nextNode = NULL;
        first = first->next;
        end = end->next;

        while (first != end)
        {
            nextNode = first->next;
            first->next = head;
            head = first;
            first = nextNode;
        }

        tail->next = end;
        return head;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    ListNode n1(1);
    ListNode n2(2);
    ListNode n3(3);
    ListNode n4(4);
    ListNode n5(5);

    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;

    Solution so;
    ListNode* result = so.swapPairs(&n1);

    return 0;
}

