// Clone_Graph.cpp : 定义控制台应用程序的入口点。
//

/*****************************************************************************************
    Clone an undirected graph.Each node in the graph contains a label and a list of its neighbors.

    OJ's undirected graph serialization:
    Nodes are labeled uniquely.

    We use # as a separator for each node, and, as a separator for node label and each neighbor of the node.
    As an example, consider the serialized graph{ 0, 1, 2#1, 2#2, 2 }.

    The graph has a total of three nodes, and therefore contains three parts as separated by #.

    First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
    Second node is labeled as 1. Connect node 1 to node 2.
    Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self - cycle.
    Visually, the graph looks like the following :

    1
    / \
    / \
    0 -- - 2
    / \
    \_ /
****************************************************************************************/

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

#define DEFAULT_STACK_SIZE 30000

template <class T>
class MyStack
{
public:
    MyStack(int size = DEFAULT_STACK_SIZE)
    {
        this->maxSize = size;
        arr = new T[size];
        top = 0;
    }

    ~MyStack()
    {
        if (arr)
        {
            delete[] arr;
        }
    }

    bool Push(T elem)
    {
        if (top == maxSize)
        {
            return false;
        }

        arr[top++] = elem;
        return true;
    }

    bool Pop(T& elem)
    {
        if (top == 0)
        {
            return false;
        }

        elem = arr[--top];
        return true;
    }

    bool IsEmpty()
    {
        return (top == 0);
    }

    bool IsFull()
    {
        return (top == maxSize);
    }

    T& Peak()
    {
        T e;
        if (IsEmpty())
        {
            return e;
        }

        return arr[top - 1];
    }

private:
    T*  arr;
    int maxSize;
    int top;
};

 typedef struct __UndirectedGraphNode {
     int label;
     vector<__UndirectedGraphNode *> neighbors;
     __UndirectedGraphNode(int x) : label(x) {};
 }UndirectedGraphNode;

 typedef struct _Elem
 {
     int step;
     int waitingChild;
     UndirectedGraphNode* node;
     UndirectedGraphNode* RetChildNode;
 }Elem;

 //The algorithm when the graph is either bidirectional or one-way connect.
class Solution {
public:

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *root) {
        UndirectedGraphNode *newRoot = cloneGraphWithAddingFlagNonRecursive(root);
        RemoveAddedFlagsNonRecursive(root);

        return newRoot;
    }

private:
    UndirectedGraphNode *cloneGraphWithAddingFlag(UndirectedGraphNode *root) {
        if (root == NULL)
            return NULL;

        UndirectedGraphNode* newRoot = new UndirectedGraphNode(root->label);
        int n = root->neighbors.size();
        int childSize;
        UndirectedGraphNode* child, *newChild;

        //Push new node's address into the original node to form a mapping,
        //and push a NULL as a label
        root->neighbors.push_back(newRoot);
        root->neighbors.push_back(NULL);

        for (int i = 0; i < n; i++)
        {
            child = root->neighbors.at(i);
            if (child == root)
            {
                newRoot->neighbors.push_back(newRoot);
                continue;
            }

            childSize = child->neighbors.size();

            if (childSize >= 2 && child->neighbors.at(childSize - 1) == NULL) //child is a visited node, which is actually our parent
            {
                newRoot->neighbors.push_back(child->neighbors.at(childSize - 2));
                continue;
            }

            newChild = cloneGraph(child);
            newRoot->neighbors.push_back(newChild);
        }

        /* This node has been visited. This should be a persistent info, which could not be removed here because its parent node
             may has not visited it and will visit it later. When the parent node visits it later, this node should use this info to tell it has
             been visited.
        root->neighbors.pop_back(); //remove the flag and mapping info
        root->neighbors.pop_back();
        */

        return newRoot;        
    }

    void RemoveAddedFlags(UndirectedGraphNode *root) {
        if (root == NULL)
            return;

        int childNum = root->neighbors.size();

        if (childNum == 0)
            return;

        if (root->neighbors.at(childNum - 1) != NULL)
            return;   //already removed

        assert(childNum >= 2);

        root->neighbors.pop_back();
        root->neighbors.pop_back();

        childNum -= 2;
        assert(childNum == root->neighbors.size());

        for (int i = 0; i < childNum; i++)
        {
            RemoveAddedFlags(root->neighbors[i]);
        }
    }

    UndirectedGraphNode *cloneGraphWithAddingFlagNonRecursive(UndirectedGraphNode *root) {
        if (root == NULL)
            return NULL;

        MyStack<Elem>   stack;
        Elem e = {0, 0, root, NULL};
        stack.Push(e);

        while (!stack.IsEmpty())
        {
            if (stack.Peak().step == 0)
            {
                int n = stack.Peak().node->neighbors.size();
                if (n >= 2 && stack.Peak().node->neighbors.at(n - 1) == NULL)
                {
                    stack.Pop(e);
                    if (!stack.IsEmpty())
                    {
                        stack.Peak().RetChildNode = e.node->neighbors.at(n - 2);
                    }
                    continue;
                }

                UndirectedGraphNode* newRoot = new UndirectedGraphNode(stack.Peak().node->label);
                n = stack.Peak().node->neighbors.size();

                //Push new node's address into the original node to form a mapping,
                //and push a NULL as a label
                stack.Peak().node->neighbors.push_back(newRoot);
                stack.Peak().node->neighbors.push_back(NULL);

                if (n == 0)
                {
                    stack.Pop(e);
                    if (!stack.IsEmpty())
                    {
                        stack.Peak().RetChildNode = newRoot;
                    }
                    continue;
                }

                stack.Peak().step = 1;
                stack.Peak().waitingChild = 0;
                e.node = stack.Peak().node->neighbors.at(0);
                e.step = 0;
                stack.Push(e);

                continue;
            }
            
            int childSize = stack.Peak().node->neighbors.size() - 2;

            stack.Peak().node->neighbors.at(childSize)->neighbors.push_back(stack.Peak().RetChildNode);
            stack.Peak().waitingChild++;

            if (stack.Peak().waitingChild == childSize)
            {
                stack.Pop(e);
                if (!stack.IsEmpty())
                {
                    stack.Peak().RetChildNode = e.node->neighbors.at(e.node->neighbors.size()-2);
                }
                continue;                
            }

            e.node = stack.Peak().node->neighbors.at(stack.Peak().waitingChild);
            e.step = 0;
            e.waitingChild = 0;
            stack.Push(e);
        }

        return e.node->neighbors.at(e.node->neighbors.size() - 2);
    }

    void RemoveAddedFlagsNonRecursive(UndirectedGraphNode *root) {
        if (root == NULL)
            return;

        MyStack<Elem>   stack;
        Elem e;
        e.node = root;
        e.step = 0;
        stack.Push(e);

        while (!stack.IsEmpty())
        {
            if (stack.Peak().step == 0)
            {
                int childNum = root->neighbors.size();

                if (childNum == 0 || stack.Peak().node->neighbors.at(childNum - 1) != NULL)
                {
                    stack.Pop(e);
                    continue;
                }

                assert(childNum >= 2);

                root->neighbors.pop_back();
                root->neighbors.pop_back();

                childNum -= 2;
                assert(childNum == root->neighbors.size());
                if (childNum == 0)
                {
                    stack.Pop(e);
                    continue;
                }

                stack.Peak().step = 1;
                stack.Peak().waitingChild = 0;
                e.node = stack.Peak().node->neighbors.at(0);
                e.step = 0;
                e.waitingChild = 0;
                stack.Push(e);
                continue;
            }

            stack.Peak().waitingChild++;
            if (stack.Peak().waitingChild == stack.Peak().node->neighbors.size())
            {
                stack.Pop(e);
                continue;
            }

            e.node = stack.Peak().node->neighbors.at(stack.Peak().waitingChild);
            e.step = 0;
            stack.Push(e);            
        }

    }




};



int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> k;
    k.push_back(2);
    k.push_back(3);
    k.push_back(4);
    k.push_back(5);

    k.pop_back();
    k.pop_back();

    UndirectedGraphNode * node1 = new UndirectedGraphNode(-1);
    UndirectedGraphNode * node2 = new UndirectedGraphNode(1);
    node1->neighbors.push_back(node2);

    Solution so;
    node2 = so.cloneGraph(node1);

	return 0;
}

