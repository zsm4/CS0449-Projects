#ifndef MY_MALLOC_H
#define MY_MALLOC_H

void *my_worstfit_malloc(int size); //check for largest available free block but if none allocate more space and put on end
void my_free(void *ptr);

#endif

