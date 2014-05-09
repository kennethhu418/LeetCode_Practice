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

using namespace std;


 typedef struct __UndirectedGraphNode {
     int label;
     vector<__UndirectedGraphNode *> neighbors;
     __UndirectedGraphNode(int x) : label(x) {};
 }UndirectedGraphNode;

 //The algorithm when the graph is bidirectional. That is, when A connects to B., then A's neighbors record B and B's neighbors also record A.
 /*
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *root) {
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
                newRoot->neighbors.push_back(childSize - 2);
                continue;
            }

            newChild = cloneGraph(child);
            newRoot->neighbors.push_back(newChild);
        }

        root->neighbors.pop_back(); //remove the flag and mapping info
        root->neighbors.pop_back();

        return newRoot;        
    }
};
*/


//The algorithm when the graph is one way. That is, when A connects to B., then A's neighbors record B but B's neighbors do not record A.
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *root) {
        if (root == NULL)
            return NULL;

        UndirectedGraphNode* newRoot = new UndirectedGraphNode(root->label);
        int n = root->neighbors.size();
        UndirectedGraphNode* child, *newChild;

        for (int i = 0; i < n; i++)
        {
            child = root->neighbors.at(i);
            if (child == root)
            {
                newRoot->neighbors.push_back(newRoot);
                continue;
            }

            newChild = cloneGraph(child);
            newRoot->neighbors.push_back(newChild);
        }

        return newChild;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

