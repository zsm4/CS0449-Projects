#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

void *sbrk(intptr_t increment);

struct blockMeta
{
    int size;
    int free; //if 1 then free
    struct blockMeta *next; //used for free list
    struct blockMeta *prev; //used for free list
};

struct blockMeta *freeLListBase = NULL;  //start of free list
struct blockMeta * getLargestBlock(int size);

void shrinkFreeBlock(struct blockMeta *,int size);
void coalesceFreeList();
void removeFreeBlock(struct blockMeta * removeMe);
struct blockMeta * getLargestBlock(int size);

void *my_worstfit_malloc(int size) //check for largest available free block but if none allocate more space and put on end
{
    if(size<=0)  //if size is negative return NULL
    {
            return NULL;
    }

    if(size%2)  //if not even add 1
    {
        size++;
    }

    int actualSize = size + sizeof(struct blockMeta);
    struct blockMeta * begOfBlock = 0;
    struct blockMeta * largestBlock = getLargestBlock(size);    //get largest block

    if(largestBlock != NULL && largestBlock->size >= size)  //allocate part of free block(as much as needed)
    {
        shrinkFreeBlock(largestBlock,size); //shrink free block by actualSize of free block allocated
        begOfBlock = largestBlock;
        struct blockMeta *block = begOfBlock;
        block->free = 0;
        block->next = NULL;
        block->prev = NULL;
    }
    else    //allocate more space
    {
        begOfBlock = (void *)sbrk(actualSize);  //allocate space on head for size and meta data
        struct blockMeta *block = begOfBlock;    //initialize blockMeta to beginning of sbrk return value
        block->size = size;
        block->free = 0;
        block->next = NULL;
        block->prev = NULL;
    }

    if(begOfBlock == (void *)-1)    //if sbrk returned (void *)-1 then return -1
    {
        return (void *)-1;
    }

    return (void *)begOfBlock + sizeof(struct blockMeta);
}

void my_free(void *ptr)
{
    //get the size of the block
    int blockSize = 0;
    int *addressOfSize;
    struct blockMeta *thisBlock = (ptr-sizeof(struct blockMeta));

    blockSize = thisBlock->size;
    thisBlock->free = 1;    //set free int to 1

   if(freeLListBase == NULL)   //if free list is empty append to beginning
    {
        freeLListBase = thisBlock;
        thisBlock->next = NULL;
        thisBlock->prev = NULL;
    }
    else    //add to end of list
    {
        struct blockMeta * current = freeLListBase;
        while(current->next)
        {
            current = current->next;
        }
        current->next = thisBlock;
        thisBlock->prev = current;
        thisBlock->next = NULL;
    }
    coalesceFreeList(); //coalesce the free list and remove any free blocks at the end of the heap with (sbrk(-(size+sizeof(metablock))))
}

struct blockMeta * getLargestBlock(int size)
{
    if(freeLListBase == NULL)
    {
        return NULL;
    }
    struct blockMeta * largestBlock = freeLListBase;
    struct blockMeta * currentBlock = freeLListBase;

    while(currentBlock->next)
    {
        currentBlock = currentBlock->next;
        if(currentBlock->size > largestBlock->size)
        {
            largestBlock = currentBlock;
        }
    }
    return largestBlock;
};

void shrinkFreeBlock(struct blockMeta * shrinkMe,int size)      //shrink free block forward by size, is size == shrinkMe->size then remove from list
{
    //if there is any "extra space" that isn't big enough to make a new block(sizeOf(struct metaBlock)+2) then add that to size
    //set shrinkMe to "size" and create a new freeNode with the remaining space. Finally add this nod to the freeList.

    int sizeOfBlock = shrinkMe->size;   //doesn't include blockMeta
    int extraBytes = sizeOfBlock-size-sizeof(struct blockMeta);    //bytes that may be used for another freeBlock
    struct blockMeta * newFreeBlock = NULL;
    removeFreeBlock(shrinkMe);  //remove shrinkMe from free list

    if(extraBytes>=2)    //there is enough extra bytes for another allocation otherwise do nothing
    {
        newFreeBlock = (struct blockMeta *)((long)shrinkMe + sizeof(struct blockMeta) + size);
        shrinkMe->size = size;
        newFreeBlock->size = extraBytes;
        newFreeBlock->free = 1;

        //add FreeBlock to free list
        if(freeLListBase == NULL)
        {
            freeLListBase = newFreeBlock;
            newFreeBlock->next = NULL;
            newFreeBlock->prev = NULL;
        }
        else
        {
            struct blockMeta * lastFreeBlock = freeLListBase;
            while(lastFreeBlock->next)
            {
                lastFreeBlock = lastFreeBlock->next;
            }
            lastFreeBlock->next = newFreeBlock;
            newFreeBlock->prev = lastFreeBlock;
            newFreeBlock->next = NULL;
        }
    }
}

void coalesceFreeList() //coalesce the FreeList and if there is a free block at the end of heap then shrink heap
{
    struct blockMeta * current = freeLListBase;
    struct blockMeta * adjacentBlock = NULL;
    struct blockMeta * adjacentNext = NULL;
    struct blockMeta * adjacentPrev = NULL;
    int coalesced = 0;
    do
    {
        coalesced = 0;
        while(current && (long)current+current->size+sizeof(struct blockMeta)<(long)sbrk(0))  //walk through free list
        {
            coalesced = 0;
            adjacentBlock = (struct blockMeta *)((long)current+current->size+sizeof(struct blockMeta));
            if(adjacentBlock->free == 1) //then coalesce blocks remove adjacent block from free list and current->size = current->size +
            {
                removeFreeBlock(adjacentBlock);
                current->size = current->size + sizeof(struct blockMeta) + adjacentBlock->size;
                coalesced = 1;
            }
            current = current->next;
        }
    }
    while(coalesced == 1);

    //check all free Blocks to see if they are at the end of the heap. If so then shrink the heap
    int found = 0;
    do
    {
        struct blockMeta * freeBlock = freeLListBase;
        found = 0;
        while(freeBlock)
        {
            if(((long)freeBlock+freeBlock->size+sizeof(struct blockMeta)) == ((long)sbrk(0)))  //if free block is at the end of the heap shrink the heap and remove freeblock from free list
            {
                found = 1;
                removeFreeBlock(freeBlock);    //remove freeBlock from free list
                sbrk(-(freeBlock->size+sizeof(struct blockMeta)));  //shrink heap
            }
            if((long)freeBlock<(long)sbrk(0))
            {
                freeBlock = freeBlock->next;
            }
            else
            {
                return;
            }
        }
    }
    while(found == 1);
}

void removeFreeBlock(struct blockMeta * removeMe)   //remove removeMe from free list
{
    struct blockMeta *prev = removeMe->prev;
    struct blockMeta *next = removeMe->next;

    if(prev && next)    //there is a previous and next block
    {
        prev->next = next;
        next->prev = prev;
    }
    else if(prev)    //no next block
    {
        prev->next = NULL;
    }
    else if(next)    //no prev block
    {
        next->prev = NULL;
        freeLListBase = next;
    }
    else{
        freeLListBase = NULL;
    }
}






