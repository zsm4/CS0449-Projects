mymalloc.c readMe
My malloc implements a worst-fit algorithm with a free node linked list.  Allocated blocks also contain a node but the next and prev pointers are set to null;

myMallocTester.c readMe
My malloc tester makes a number of allocations and deallocations.  After each allocation/deallocation it prints the entire heap fallowed by the entire freeBlock linked list.  You can easily observe that the malloc correctly allocates and deallocates memory as well as shrinking the heap and coalescing blocks.

How to compile the project: gcc mallocdrv.c mymalloc.c