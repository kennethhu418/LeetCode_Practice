// Partition_List.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


typedef struct __ListNode {
    int val;
    __ListNode *next;
    __ListNode(int x) : val(x), next(NULL) {}
}ListNode;

class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode* lessHead = NULL, *lessTail = NULL;
        ListNode* greaterHead = NULL, *greaterTail = NULL;

        while (head)
        {
            if (head->val < x)
            {
                if (lessHead == NULL)
                    lessHead = lessTail = head;
                else
                {
                    lessTail->next = head;
                    lessTail = head;
                }
            }
            else
            {
                if (greaterHead == NULL)
                    greaterHead = greaterTail = head;
                else
                {
                    greaterTail->next = head;
                    greaterTail = head;
                }
            }

            head = head->next;
        }

        if (greaterTail)
            greaterTail->next = NULL;

        if (!lessHead)
            return greaterHead;

        lessTail->next = greaterHead;
        return lessHead;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

