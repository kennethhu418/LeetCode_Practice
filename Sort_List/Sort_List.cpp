// Sort_List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct __ListNode {
    int val;
    __ListNode *next;
    __ListNode(int x) : val(x), next(NULL) {}
}ListNode;

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode* tail = NULL, *prevTail = NULL, *nextHead = NULL;
        mergeUnit = 1;

        while (true)
        {
            head = sortCurrentUnit(head, tail);
            if (tail->next == NULL)
                break;

            prevTail = tail;
            while (prevTail->next)
            {
                prevTail->next = sortCurrentUnit(prevTail->next, tail);
                prevTail = tail;
            }

            mergeUnit *= 2;
        }

        return head;
    }

private:
    unsigned int mergeUnit;
    ListNode* curHead1;
    ListNode* curTail1;
    ListNode* curHead2;
    ListNode* curTail2;

    inline ListNode* sortCurrentUnit(ListNode* head, ListNode* &tail)
    {
        if (head == NULL)
            return NULL;

        tail = NULL;
        ListNode* nextNode = NULL;

        curHead1 = head;
        curTail1 = getNodeByIndex(curHead1, mergeUnit - 1);
        if (curTail1->next == NULL)
        {
            tail = curTail1;
            return curHead1;
        }

        curHead2 = curTail1->next;
        curTail2 = getNodeByIndex(curHead2, mergeUnit - 1);

        nextNode = curTail2->next;
        curTail1->next = NULL;
        curTail2->next = NULL;

        head = mergeLists(curHead1, curHead2, tail);
        tail->next = nextNode;
        return head;
    }

    inline ListNode* getNodeByIndex(ListNode* head, unsigned int targetIndex)
    {
        unsigned int curIndex = 0;
        ListNode* prevNode = NULL;

        while (head)
        {
            if (curIndex == targetIndex)
                return head;
            prevNode = head;
            head = head->next;
            curIndex++;
        }

        return prevNode;
    }

    inline ListNode* mergeLists(ListNode* list1, ListNode* list2, ListNode* &tail)
    {
        ListNode* head = NULL;
        tail = NULL;

        while (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                if (head == NULL)
                    head = tail = list1;
                else
                {
                    tail->next = list1;
                    tail = list1;
                }
                list1 = list1->next;
            }
            else
            {
                if (head == NULL)
                    head = tail = list2;
                else
                {
                    tail->next = list2;
                    tail = list2;
                }
                list2 = list2->next;
            }
        }

        if (list2)
            list1 = list2;

        while (list1)
        {
            if (head == NULL)
                head = tail = list1;
            else
            {
                tail->next = list1;
                tail = list1;
            }
            list1 = list1->next;
        }

        tail->next = NULL;
        return head;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}