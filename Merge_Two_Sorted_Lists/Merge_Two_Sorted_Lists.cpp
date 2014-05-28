// Merge_Two_Sorted_Lists.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


typedef struct __ListNode {
    int val;
    __ListNode *next;
    __ListNode(int x) : val(x), next(NULL) {}
}ListNode;

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;

        ListNode*   head = NULL, *tail = NULL;
        ListNode*   curSmallNode = NULL;
        while (l1 && l2)
        {
            curSmallNode = l1->val <= l2->val ? l1 : l2;
            if (curSmallNode == l1)
                l1 = l1->next;
            else
                l2 = l2->next;

            if (head == NULL)
                head = tail = curSmallNode;
            else
            {
                tail->next = curSmallNode;
                tail = curSmallNode;
            }
        }

        if (l1)
            tail->next = l1;
        else
            tail->next = l2;

        return head;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

