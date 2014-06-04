#ifndef _WINNER_TREE_INNER_
#define _WINNER_TREE_INNER_

#include <assert.h>

template <class T> //T is the values' type stored in this stream
class Stream
{
public:
    virtual bool empty() const = 0;
    virtual T& getFirstElem() = 0;
    virtual void removeFirstElem() = 0;
    virtual int compare(const T& t1, const T& t2) = 0;
};

template <class T>  //T is the value that will be compared
class WinnerTree
{
public:
    bool    Initialize(Stream<T>* streams, int n)
    {
        if (n < 1)
            return false;
        this->K = n;

        if (K == 1)
        {
            array = new int[1];
            array_size = 1;
            leaf_start = 0;
            return true;
        }

        //get the size of the array for the winner tree
        int curMask = 0x80000000;
        while (curMask & K == 0)
            curMask = curMask >> 1;
        assert(curMask);

        if (curMask != K)
            curMask << 1;        
        n = curMask;

        array_size = 2 * n - 1;   //full perfect binary tree's size
        array_size = array_size - (array_size - K) * 2; //perfect binary tree's size with K leaves
        leaf_start = array_size - K;
        array = new int[array_size];
        assert(array);

        //first fill the leaves
        for (int i = 0; i < K; i++)
            array[leaf_start + i] = i;

        //fill the non-leaf nodes
        int p = 0, leftIndex = 0, rightIndex = 0;
        for (int i = array_size - 1; i > 0; i -= 2)
        {
            p = (i - 1) / 2;
            leftIndex = array[i - 1];
            rightIndex = array[i];

            if (streams[rightIndex].empty())
                array[p] = leftIndex;
            else if (streams[leftIndex].empty())
                array[p] = rightIndex;
            else
            {
                if (streams[leftIndex].compare(streams[leftIndex].getFirstElem(), streams[rightIndex].getFirstElem()) < 0)
                    array[p] = leftIndex;
                else
                    array[p] = rightIndex;
            }            
        }

        return true;
    }

    void    FreeTree()
    {
        if (array)
            delete[] array;
        array = NULL;
        array_size = 0;
        leaf_start = 0;
    }

    T&       peekWinner()
    {
        return streams[array[0]].getFirstElem();
    }

    T           takeWinner()
    {
        T   retVal = streams[array[0]].getFirstElem();

        int changedNode = leaf_start + array[0];
        streams[array[0]].removeFirstElem();

        int p, slibling, index1, index2;
        while (changedNode > 0)
        {
            p = changedNode & 0x1 ? changedNode / 2 : (changedNode - 1) / 2;
            slibling = changedNode & 0x1 ? changedNode + 1 : changedNode - 1;

            index1 = array[changedNode];
            index2 = array[slibling];

            if (streams[index1].empty())
                array[p] = index2;
            else if (streams[index2].empty())
                array[p] = index1;
            else
            {
                if (streams[index1].compare(streams[index1].getFirstElem(), streams[index2].getFirstElem()) < 0)
                    array[p] = index1;
                else
                    array[p] = index2;
            }

            changedNode = p;
        }

        return retVal;
    }

    bool    empty()
    {
        if (streams[array[0]].empty())
            return true;
        return false;
    }

private:
    Stream<T>*     streams;
    int                 K;
    int*              array;
    int                 array_size;
    int                 leaf_start;
};

#endif