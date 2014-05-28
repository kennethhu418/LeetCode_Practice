// Rotate_List.cpp : 定义控制台应用程序的入口点。
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
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode*   original_tail = NULL;
        int     size = getListSize(head, original_tail);

        k = k%size;
        if (k == 0)
            return  head;

        k = size - k;
        ListNode*   newTail = getNodeByIndex(head, k - 1);
        assert(newTail && newTail->next);

        original_tail->next = head;
        head = newTail->next;
        newTail->next = NULL;
        return head;
    }

private:
    inline int getListSize(ListNode* head, ListNode* &tail)
    {
        int     index = 0;
        tail = NULL;
        while (head)
        {
            index++;
            tail = head;
            head = head->next;
        }
        return index;
    }

    inline ListNode* getNodeByIndex(ListNode* head, int index)
    {
        if (head == NULL)
            return head;

        int  curIndex = 0;
        while (head)
        {
            if (curIndex == index)
                return head;
            curIndex++;
            head = head->next;
        }

        return NULL;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

