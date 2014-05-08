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
        {
            return head;
        }

        ListNode* curNode, *prevNodeT, *nextNodeT, *list1H, *list2H, *list1E, *list2E, *newH, *newE;
        int size = 1, totalCount = 0, curCount = 0;

        //First get total count of nodes
        curNode = head;
        while(curNode)
        {
            totalCount++;
            curNode = curNode->next;
        }

        while(size < totalCount)
        {
            curNode = head;
            prevNodeT = NULL;
            list1H = head;
            curCount = size;
            
            while(true)
            {
                //Get List1's head and end
                while(curCount)
                {
                    if (curNode == NULL)
                        break;

                    curCount--;
                    list1E = curNode;
                    curNode = curNode->next;               
                }

                if (curCount > 0)   //list 1 is not full with size count of nodes
                    break;

                if (list1E->next == NULL) //list 2 has no nodes
                    break;

                //Get List2's head and end
                list2H = list1E->next; curCount = size; curNode = list1E->next;
                while(curCount)
                {
                    if (curNode == NULL)
                        break;

                    curCount--;
                    list2E = curNode;
                    curNode = curNode->next;               
                }

                nextNodeT = list2E->next;

                //Now merge the two sorted lists
                newH = NULL; 
                newE = NULL;
                MergeSortedLists(list1H, list1E, list2H, list2E, &newH, &newE);

                //Adjust head and tail
                if (prevNodeT == NULL)
                {
                    head = newH;
                }
                else
                    prevNodeT->next = newH;

                newE->next = nextNodeT;

                list1H = newE->next;
                curCount = size;
                curNode = newE->next;
                prevNodeT = newE;
            }

            size = size<<1;
        }

        return head;        
    }

private:
    void MergeSortedLists(ListNode* list1H, ListNode* list1E, ListNode* list2H, ListNode* list2E, ListNode** newH, ListNode** newE)
    {
        if (newH == NULL || newE == NULL)
        {
            return;
        }
        
        if (list1H == NULL)
        {
            *newH = list2H;
            *newE = list2E;
            return;
        }

        if (list2H == NULL)
        {
            *newH = list1H;
            *newE = list1E;
            return;
        }

        ListNode* head = NULL, *tail = NULL, *curNode1 = list1H, *curNode2 = list2H, *list2EOL = list2E->next, *list1EOL = list1E->next;

        while(curNode1 != list1EOL && curNode2 != list2EOL)
        {
            if (curNode1->val < curNode2->val)
            {
                if (head == NULL)
                {
                    head = tail = curNode1;
                }
                else
                {
                    tail->next = curNode1;
                    tail = curNode1;
                }
                curNode1 = curNode1->next;
                continue;
            }

            if (head == NULL)
            {
                head = tail = curNode2;
            }
            else
            {
                tail->next = curNode2;
                tail = curNode2;
            }
            curNode2 = curNode2->next;
        }

        if (curNode1 != list1EOL)
        {
            tail->next = curNode1;
            tail = list1E;
        }
        else if (curNode2 != list2EOL)
        {
            tail->next = curNode2;
            tail = list2E;
        }

        *newH = head;
        *newE = tail;
        return;        
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}