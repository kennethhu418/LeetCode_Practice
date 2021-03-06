// Linked_List_Cycle_II.cpp : Defines the entry point for the console application.
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
    ListNode *hasCycle(ListNode *head) {
        if (head == NULL || head->next == head)
        {
            return head;
        }

        //Determine whether there are circle
        ListNode* node1 = head, * node2 = head;
        ListNode* encounterNode;
        int passCount;

        //Now let both node1 and node2 starting traverse from head.
        //node 1 traverse one node after node, node2 traverse by skipping one node
        //If there is circle, they must encounter at some specific node.
        encounterNode = GetEncounterNodeDifferentPace(node1, node2, passCount);
        if (encounterNode == NULL)
        {
            return NULL;
        }

        //Now let node1 starting traverse from head one node after node, and node2
        //starting traverse from encounterNode(which is one node in the circle) also
        //node after node. When they encounter, the encounter node must be the starting
        //of the circle.
        //Please see the "循环链表寻找环起点.JPG" in F:\LeetCode
        node1 = head;
        node2 = encounterNode;
        encounterNode = GetEncounterNodeSamePace(node1, node2, passCount);
        assert(encounterNode);
    
        return encounterNode;        
    }

private:
    int GetSize(ListNode* root)
    {
        if (root == NULL)
        {
            return 0;
        }

        if (root->next == root || root->next == NULL)
        {
            return 1;
        }

        int size = 1;

        ListNode* curNode = root->next;

        while(curNode != root)
        {
            size++;
            curNode = curNode->next;
            if(curNode == NULL)
                return size;
        }

        return size;
    }

    //returns the encouter node and how many nodes node1 and nodes2 passed.
    ListNode* GetEncounterNodeDifferentPace(ListNode* node1, ListNode* node2, int& passCount)
    {
        if (node1 == NULL || node2 == NULL)
        {
            passCount = 0;
            return NULL;
        }

        passCount = 1;

		//Since node1 and node2 are at the same node at first, so we must forward them first
		node1 = node1->next;
		node2 = node2->next;
		if(node2 == NULL)
			return NULL;
		node2 = node2->next;		

        while(node1 && node2)
        {
			passCount++;
            if (node1 == node2)
            {
                return node1;
            }
           
			node1 = node1->next;
            node2 = node2->next;
            if (node2 == NULL)
                return NULL;
            node2 = node2->next;
        }

        return NULL;        
    }

        //returns the encouter node and how many nodes node1 and nodes2 passed.
    ListNode* GetEncounterNodeSamePace(ListNode* node1, ListNode* node2, int& passCount)
    {
        if (node1 == NULL || node2 == NULL)
        {
            passCount = 0;
            return NULL;
        }

        passCount = 0;

        while(node1 && node2)
        {
            passCount++;

            if (node1 == node2)
            {
                return node1;
            }

            node1 = node1->next;
            node2 = node2->next;
        }

        return NULL;        
    }


};


int _tmain(int argc, _TCHAR* argv[])
{
	ListNode* node = new ListNode(1);
	node->next = node;


	Solution s;
	ListNode* start = s.hasCycle(node);

	return 0;
}

