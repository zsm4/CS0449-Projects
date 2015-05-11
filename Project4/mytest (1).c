#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mymalloc.h"

void * base;
void displayHeap();
void displayFreeList();

extern freeLListBase;

int main()
{
    base = sbrk(0);
    printf("Start of heap is %p\n",base);

    printf("Heap original\n");
    displayHeap();

    void * allocate1 = my_worstfit_malloc(20);
    printf("Heap after and allocation of 20\n");
    displayHeap();

    void * allocate2 = my_worstfit_malloc(200);
    printf("Heap after and allocation of 200\n");
    displayHeap();
    displayFreeList();

    void * allocate3 = my_worstfit_malloc(40);
    printf("Heap after and allocation of 40\n");
    displayHeap();
    displayFreeList();

    printf("Heap after free of 20\n");
    my_free(allocate1);
    displayHeap();
    displayFreeList();

    printf("Heap after free of 200\n");
    my_free(allocate2);
    displayHeap();
    displayFreeList();

    printf("Heap after allocation of 20\n");
    void * allocate4 = my_worstfit_malloc(20);
    displayHeap();
    displayFreeList();


    printf("Heap after and de-allocation of 40\n");
    my_free(allocate3);
    displayHeap();
    displayFreeList();

    printf("Heap after and de-allocation of 20\n");
    my_free(allocate4);
    displayHeap();
    displayFreeList();

    exit(1);
}

void displayHeap()
{
    printf("PRINTING THE HEAP\n");
    if(base == sbrk(0))
    {
        printf("There is nothing allocated in the heap with base at %p.\n",base);
    }
    void * current = base;


    int cnt = 1;

    while(current < sbrk(0))
    {
        struct blockMeta * block = current;
        char * freeOrNo;
        int size = *block->size;
        if(block->free == 1)
        {
            freeOrNo = "free";
        }
        else
        {
            freeOrNo = "allocated";
        }
        printf("This is block %d it starts at %p. The block is %s and contains %d bytes.\n",cnt,(void *)block,freeOrNo,size);
        current +=(sizeof(struct blockMeta)+size);
        cnt++;
    }
    printf("End of heap is at %p\n",sbrk(0));
}

void displayFreeList()
{
    int cnt = 0;
    printf("AND NOW FOR THE FREELIST\n");
    if(freeLListBase == NULL)
    {
        printf("Linked list is NULL\n");
    }
    else
    {
        struct blockMeta * current = freeLListBase;
        while(current)
        {
            printf("This is node %d it starts at %p. The block contains %d bytes the next node is at %p and the previous node is at %p.\n",cnt,(void *)current,current->size,current->next,current->prev);
            current = current->next;
            cnt++;
        }
    }
    printf("\n");
}
