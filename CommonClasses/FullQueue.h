#include "stdafx.h"
#include <assert.h>

#define DEFAULT_QUEUE_SIZE 30

template <class T>
class FullQueue
{
public:
    FullQueue(int size = DEFAULT_QUEUE_SIZE)
    {
        this->size = size;
        this->arr = NULL;
        if (size)
            this->arr = new T[size];
        this->curLen = 0;
        this->nextPos = 0;
    }

    ~FullQueue()
    {
        if (this->arr)
            delete[] this->arr;
    }

    bool    IsEmpty()
    {
        return curLen == 0;
    }

    bool IsFull()
    {
        return curLen == size;
    }

    void    Push(const T& target)
    {
        arr[nextPos] = target;
        if (curLen < size)
            curLen++;
        nextPos = (nextPos + 1) % size;
    }

    T&      Front()
    {
        assert(curLen > 0);
        if (curLen < size)
            return arr[0];

        return arr[nextPos];
    }

    T&    GetLatest(int i)
    {
        assert(i < curLen);
        int     pos = (size + nextPos - i - 1) % size;
        return arr[pos];
    }


private:
    int     size;
    T       *arr;
    int     curLen;
    int     nextPos;    
};