// Add_Two_Numbers.cpp : 定义控制台应用程序的入口点。
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;

        this->freeNodes = NULL;

        ListNode* head = NULL, *tail = NULL, *nextNode = NULL;
        bool carry_on = false;
        int curResult = 0;

        while (l1 && l2)
        {
            curResult = l1->val + l2->val;
            if (carry_on)
                curResult++;

            if (curResult > 9)
            {
                carry_on = true;
                curResult -= 10;
            }
            else
                carry_on = false;

            l1->val = curResult;
            nextNode = l2->next;

            addFreeNode(l2);
            if (head == NULL)
            {
                head = tail = l1;
            }
            else
            {
                tail->next = l1;
                tail = l1;
            }

            l1 = l1->next;
            l2 = nextNode;
        }

        if (l2)
            l1 = l2;

        while (l1)
        {
            l1->val = l1->val + (carry_on ? 1 : 0);
            if (l1->val > 9)
            {
                l1->val -= 10;
                carry_on = true;
            }
            else
                carry_on = false;
            tail->next = l1;
            tail = l1;
            l1 = tail->next;
        }

        if (carry_on)
        {
            l1 = getFreeNode();
            assert(l1);
            l1->val = 1;
            tail->next = l1;
            tail = l1;
        }

        tail->next = NULL;
        return head;
    }

private:
    ListNode* freeNodes;

    inline void addFreeNode(ListNode* freeNode)
    {
        if (freeNodes)
        {
            freeNode->next = freeNodes;
            freeNodes = freeNode;
        }
        else
        {
            freeNodes = freeNode;
        }
    }

    inline ListNode* getFreeNode()
    {
        if (freeNodes == NULL)
            return NULL;

        ListNode*   retNode = freeNodes;
        freeNodes = freeNodes->next;
        return retNode;
    }    
};


int _tmain(int argc, _TCHAR* argv[])
{
    ListNode node11(8);
    ListNode node12(3);
    ListNode node13(9);
    node11.next = &node12;
    node12.next = &node13;

    ListNode node21(9);
    ListNode node22(6);
    node21.next = &node22;

    Solution so;
    ListNode* result = so.addTwoNumbers(&node11, &node21);
    
	return 0;
}

