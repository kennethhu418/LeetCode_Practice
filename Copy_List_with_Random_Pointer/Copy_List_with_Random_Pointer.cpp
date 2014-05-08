// Copy_List_with_Random_Pointer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


typedef struct __RandomListNode {
    int label;
    __RandomListNode *next, *random;
    __RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
}RandomListNode;

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        //First create the new list.
        //The new node's random field is used to store the original
        //random field value in the old node. And the old node's
        //random field is now storing the address of the corresponding
        //new node. Thus the random field in the old node offers the
        //mapping information between old node and new node.
        RandomListNode* head2 = CreateNewRawListWithMapping(head);

        //Secondly construct the new list nodes' random fields.
        //The original random field value of the new node (which stores
        //the original random field value of the old node) is stored
        //to the next field of the new node.
        //After this function, the new lists are broken.
        ConstructRandomFieldsInNewList(head2);

        //Last fix the new list and restore the random field value
        //of the original list.
        ReconstructOriginalAndNewLists(head);

        return head2;        
    }

private:
    RandomListNode* CreateNewRawListWithMapping(RandomListNode *head)
    {
        RandomListNode* curNode;
        RandomListNode* prevNode = NULL, *head2 = NULL;

        while(head)
        {
            curNode = new RandomListNode(head->label);
            curNode->random = head->random; //save original list node's random in new node
            head->random = curNode;  //save mapping infor in original list node
            if (prevNode != NULL)
            {
                prevNode->next = curNode;
            }
            else
            {
                head2 = curNode;
            }
            
            prevNode = curNode;
            head = head->next;
        }

        return head2;
    }

    void ConstructRandomFieldsInNewList(RandomListNode* newHead)
    {
        RandomListNode* newCurNode = newHead;
        RandomListNode* randNodeInOrgList = NULL;
        RandomListNode* nextNode = NULL;

        while (newCurNode)
        {
            nextNode = newCurNode->next;

            randNodeInOrgList = newCurNode->random;
            if(randNodeInOrgList)
            {
                newCurNode->random = randNodeInOrgList->random;
            }

            newCurNode->next = randNodeInOrgList;

            newCurNode = nextNode;
        }
    }

    void ReconstructOriginalAndNewLists(RandomListNode* head)
    {
        RandomListNode* curNode;

        while(head)
        {
            curNode = head->random;  //the node in the new list

            head->random = curNode->next;  //resume the random field of the original list node
            
            //resume the next field of the new list node;
            curNode->next = NULL;
            if (head->next)
            {
                curNode->next = head->next->random;
            }

            head = head->next;
        }
        
    }


};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

