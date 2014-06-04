// CommonClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "MyStack.h"
#include "WinnerTree.h"

using namespace std;

typedef struct __ListNode
{
    int val;
    __ListNode* next;
    __ListNode(int val = 0){ this->val = val; next = NULL; }

}ListNode;

class ListStream : public Stream<ListNode*>
{
public:
    ListStream(ListNode* list = NULL)
    { 
        this->head = list; 
    }

    bool empty() const
    {
        return head == NULL;
    }

    ListNode*& getFirstElem()
    {
        return head;
    }

    void removeFirstElem()
    {
        if (head != NULL)
            head = head->next;
    }

    int compare(ListNode* &t1, ListNode* &t2)
    {
        return t1->val - t2->val;
    }

private:
    ListNode* head;
};


int _tmain(int argc, _TCHAR* argv[])
{
    MyStack<int> stack;

    stack.Push(3);
    stack.Peak() = 10;

    int a;
    stack.Pop(a);

    printf("%d\n", a);

    ListNode node1(3);
    ListNode node2(10);
    ListNode node3(30);
    node1.next = &node2;
    node2.next = &node3;

    ListNode lnode1(2);
    ListNode lnode2(13);
    ListNode lnode3(24);
    lnode1.next = &lnode2;
    lnode2.next = &lnode3;

    ListNode llnode1(8);
    ListNode llnode2(33);
    llnode1.next = &llnode2;

    ListStream  stream1(&node1);
    ListStream  stream2(&lnode1);
    ListStream  stream3(&llnode1);

    vector<Stream<ListNode*>*> streamArray;
    streamArray.push_back(&stream1);
    streamArray.push_back(&stream2);
    streamArray.push_back(&stream3);

    WinnerTree<ListNode*>   winnerTree;
    winnerTree.Initialize(streamArray);

    cout << "Winner Tree Output: " << endl;
    while (!winnerTree.empty())
    {
        cout << winnerTree.peekWinner()->val << " ";
        winnerTree.takeWinner();
    }
    cout << endl << endl;

    winnerTree.FreeTree();

    system("PAUSE");
	return 0;
}

