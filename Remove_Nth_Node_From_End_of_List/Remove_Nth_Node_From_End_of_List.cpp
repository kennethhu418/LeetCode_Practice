// Remove_Nth_Node_From_End_of_List.cpp : 定义控制台应用程序的入口点。
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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (head == NULL) return NULL;
        if (n == 0) return head;
        if (head->next == NULL) return NULL;

        ListNode* forwardNode = moveOnForKNodes(head, n - 1);
        ListNode* backwardNode = head;
        if (forwardNode->next == NULL)
            head = head->next;
        else
        {
            while (forwardNode)
            {
                assert(forwardNode->next);
                if (forwardNode->next->next == NULL)
                {
                    assert(backwardNode->next);
                    backwardNode->next = backwardNode->next->next;
                    break;
                }
                forwardNode = forwardNode->next;
                backwardNode = backwardNode->next;
            }
        }

        return head;
    }

private:
    inline ListNode* moveOnForKNodes(ListNode* startNode, int k)
    {
        int curNodes = 0;
        while (curNodes < k)
        {
            assert(startNode);
            startNode = startNode->next;
            curNodes++;
        }
        return startNode;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

