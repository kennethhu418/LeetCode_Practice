// Remove_Duplicates_from_Sorted_List.cpp : 定义控制台应用程序的入口点。
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
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode*   resultHead = NULL, *resultTail = NULL;
        ListNode*   curStart = head, *curEnd = head;

        while (curStart)
        {
            curEnd = curStart;

            //first find duplicates
            while (curEnd->next && curEnd->next->val == curStart->val)
                curEnd = curEnd->next;

            //Now remove the duplicates
            if (resultHead == NULL)
                resultHead = resultTail = curStart;
            else
            {
                assert(resultTail);
                resultTail->next = curStart;
                resultTail = curStart;
            }

            curStart = curEnd->next;
        }

        assert(resultTail);
        resultTail->next = NULL;
        return resultHead;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

