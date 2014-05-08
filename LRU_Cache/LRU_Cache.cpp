// LRU_Cache.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>

typedef struct _Record
{
    int key;        //key of hash
    int value;      //record value
    _Record* next;  //the prev link on the LRU list or on the free list
    _Record* prev;  //the next link on the LRU list or on the free list
}Record;


class LRUCache{
public:
    LRUCache(int capacity) {
        recordBuffer = NULL;
        freePool = NULL;
        LRUList_head = NULL;
        LRUList_tail = NULL;
		current_count = 0;

        this->capacity = capacity;

        if (capacity == 0)
        {
            return;
        }

        recordBuffer = new char[capacity*sizeof(Record)];
        for (int i = 0; i < capacity; i++)
        {
            Record* curRecord = (Record*)(recordBuffer + sizeof(Record)*i);
            ReturnRecordToFreePool(curRecord);
        }        
    }

    int get(int key) {
        if (hash.find(key) == hash.end())
        {
            return -1;
        }

        Record* curRecord = hash[key];

        //If it is already the most recent accessed record, do nothing
        if (LRUList_tail != curRecord)
        {
            Record* preRecord = curRecord->prev;
            Record* nextRecord= curRecord->next;

            if (preRecord == NULL)
            {
                LRUList_head = nextRecord;
                nextRecord->prev = NULL;
            }
            else
            {
                preRecord->next = nextRecord;
                nextRecord->prev = preRecord;
            }
            curRecord->prev = LRUList_tail;
            LRUList_tail->next = curRecord;
            curRecord->next = NULL;
            LRUList_tail = curRecord;
        }

        return curRecord->value;
    }

    void set(int key, int value) {
		if (hash.find(key) != hash.end()) //already exists, just renew the value.
		{
			Record* curRecord = hash[key];
			curRecord->value = value;

			//If it is already the most recent accessed record, do nothing
			if (LRUList_tail != curRecord)
			{
				Record* preRecord = curRecord->prev;
				Record* nextRecord= curRecord->next;

				if (preRecord == NULL)
				{
					LRUList_head = nextRecord;
					nextRecord->prev = NULL;
				}
				else
				{
					preRecord->next = nextRecord;
					nextRecord->prev = preRecord;
				}
				curRecord->prev = LRUList_tail;
				LRUList_tail->next = curRecord;
				curRecord->next = NULL;
				LRUList_tail = curRecord;
			}

			return;
		}

        if (capacity == 0)
        {
            return;
        }

        //If already full, remove the oldest one for new one's space
        if (current_count == capacity)
        {
            Record* targetRecord = RemoveOldestRecord();            
            ReturnRecordToFreePool(targetRecord);
            current_count--;
        }

        //Take one free record
        Record* newRecord = GetFreeRecord();
        newRecord->key = key;
        newRecord->value = value;
        newRecord->prev = newRecord->next = NULL;

        hash[key] = newRecord;

        //Put it into LRU list
        AddRecordToLRU(newRecord);  

        current_count++;
    }

    ~LRUCache()
    {
        if (recordBuffer)
        {
            delete [] recordBuffer;
        }
    }

private:

    Record* GetFreeRecord()
    {
        if (freePool == NULL)
        {
            return NULL;
        }

        Record* freeRecord = freePool;
        if (freePool->next == NULL)
        {
            freePool = NULL;
        }
        else
        {
            freePool->next->prev = NULL;
            freePool = freePool->next;
        }
        
        freeRecord->next = NULL;
        return freeRecord;
    }

    void ReturnRecordToFreePool(Record* record)
    {
        if (record == NULL)
        {
            return;
        }

        record->prev = record->next = NULL;

        if (freePool == NULL)
        {
            freePool = record;
            return;
        }

        freePool->prev = record;
        record->next = freePool;
        freePool = record;
        return;
    }

    Record* RemoveOldestRecord()
    {
        if (LRUList_head == NULL)
        {
            return NULL;
        }

        Record* target = LRUList_head;
        hash.erase(target->key);

        if (LRUList_head->next == NULL)
        {
            LRUList_head = LRUList_tail = NULL;
            return target;
        }

        LRUList_head->next->prev = NULL;
        LRUList_head = LRUList_head->next;
        target->prev = target->next = NULL;
        return target;
    }

    void AddRecordToLRU(Record* record)
    {
        if (record == NULL)
        {
            return;
        }

        record->prev = record->next = NULL;

        if(LRUList_head == NULL)
        {
            LRUList_head = LRUList_tail = record;
            return;
        }

        LRUList_tail->next = record;
        record->prev = LRUList_tail;
        LRUList_tail = record;
    }

    int capacity;       //max size of the cache in unit of record count
    int current_count;  //current count of records.
    char*   recordBuffer;
    Record* freePool;   //free records are placed on this list
    Record* LRUList_head;    //LRU list head, which is the oldest record.
    Record* LRUList_tail;    //LRU list tail, which is the most recently accessed record

    std::map<int, Record*>  hash;   //hashtable to search the record by key
};


int _tmain(int argc, _TCHAR* argv[])
{
	LRUCache cache(1);

	//set(2,1),get(2),set(3,2),get(2),get(3)

	cache.set(2,1);
	cache.get(2);
	cache.set(3,2);
	cache.get(2);
	cache.get(3);

    return 0;
}

