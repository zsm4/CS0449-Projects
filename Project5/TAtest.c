//You only test case, should be similar to mallocdrv.c
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//include your code
#include "mymalloc.h"
//
////replace malloc here with the appropriate version of mymalloc
#define MALLOC malloc
////replace free here with the appropriate version of myfree
#define FREE free
//

void test1()
{
	printf("\nInitial base is %p\n\n", sbrk(0));
	
	printf("Going to add ten items of size 50 to the heap...\n");
	
	int * one = (int *)MALLOC(50);
	printf("\nAdded first item: sbrk(0) = %p\n", sbrk(0));
	int * two = (int *)MALLOC(50);
	printf("Added second item: sbrk(0) = %p\n", sbrk(0));
	int * three = (int *)MALLOC(50);
	printf("Added third item: sbrk(0) = %p\n", sbrk(0));
	int * four = (int *)MALLOC(50);
	printf("Added fourth item: sbrk(0) = %p\n", sbrk(0));
	int * five = (int *)MALLOC(50);
	printf("Added fifth item: sbrk(0) = %p\n", sbrk(0));
	int * six = (int *)MALLOC(50);
	printf("Added sixth item: sbrk(0) = %p\n", sbrk(0));
	int * seven = (int *)MALLOC(50);
	printf("Added seventh item: sbrk(0) = %p\n", sbrk(0));
	int * eight = (int *)MALLOC(50);
	printf("Added eighth item: sbrk(0) = %p\n", sbrk(0));
	int * nine = (int *)MALLOC(50);
	printf("Added ninth item: sbrk(0) = %p\n", sbrk(0));
	int * ten = (int *)MALLOC(50);
	
	printf("After adding the tenth item of size 50 each, sbrk(0) = %p\n\n",  sbrk(0));
	
	printf("Freeing the first 5 elements...sbrk(0) should remain the same\n");
	FREE(one);
	FREE(two);
	FREE(three);
	FREE(four);
	FREE(five);
	
	printf("After freeing the first five items, sbrk(0) = %p\n", sbrk(0));
	
	printf("\nFreeing the last item: sbrk(0) should decrease to where it was after adding the ninth item.\n");
	FREE(ten);
	printf("After freeing the tenth item, sbrk(0) = %p. There are now 9 items left in the heap.\n\n", sbrk(0));

	printf("Freeing the seventh and eighth items, sbrk(0) should remain the same as the ninth element is still in use:\n");
	FREE(seven);
	FREE(eight);
	printf("After freeing the seventh and eighth items, sbrk(0) = %p\n\n", sbrk(0));
	printf("Freeing the ninth (last) item. sbrk(0) should decrease to the end of the sixth item:\n");
	FREE(nine);
	printf("After freeing the ninth item, sbrk(0) = %p\n\n", sbrk(0));
	printf("Freeing the sixth item, which is the only used item in the list. sbrk(0) should go back to its original value:\n");
	FREE(six);
	printf("After freeing all items in the list, sbrk(0) = %p\n\n", sbrk(0));
}

void test2()
{
	printf("\nInitial base is %p\n\n", sbrk(0));
	
	printf("Going to add ten items of size 50 each to the heap...\n");
	
	int * one = (int *)MALLOC(50);
	printf("\nAdded first item: sbrk(0) = %p\n", sbrk(0));
	int * two = (int *)MALLOC(50);
	printf("Added second item: sbrk(0) = %p\n", sbrk(0));
	int * three = (int *)MALLOC(50);
	printf("Added third item: sbrk(0) = %p\n", sbrk(0));
	int * four = (int *)MALLOC(50);
	printf("Added fourth item: sbrk(0) = %p\n", sbrk(0));
	int * five = (int *)MALLOC(50);
	printf("Added fifth item: sbrk(0) = %p\n", sbrk(0));
	int * six = (int *)MALLOC(50);
	printf("Added sixth item: sbrk(0) = %p\n", sbrk(0));
	int * seven = (int *)MALLOC(50);
	printf("Added seventh item: sbrk(0) = %p\n", sbrk(0));
	int * eight = (int *)MALLOC(50);
	printf("Added eighth item: sbrk(0) = %p\n", sbrk(0));
	int * nine = (int *)MALLOC(50);
	printf("Added ninth item: sbrk(0) = %p\n", sbrk(0));
	int * ten = (int *)MALLOC(50);
	
	printf("After adding the tenth item of size 50 each, sbrk(0) = %p\n\n", sbrk(0));
	
	printf("Going to remove items in order they were placed (1-10). sbrk(0) should not change until the last one is freed, at which point it should go back to the initial base value.\n");
	
	FREE(one);
	printf("After the first item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(two);
	printf("After the second item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(three);
	printf("After the third item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(four);
	printf("After the fourth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(five);
	printf("After the fifth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(six);
	printf("After the sixth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(seven);
	printf("After the seventh item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(eight);
	printf("After the eighth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(nine);
	printf("After the ninth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(ten);
	printf("After the tenth (last) item is freed, sbrk(0) = %p\n", sbrk(0));
	
}

void test3()
{
	printf("\nInitial base is %p\n\n", sbrk(0));
	
	printf("Going to add ten items of size 50 each to the heap...\n");
	
	int * one = (int *)MALLOC(50);
	printf("\nAdded first item: sbrk(0) = %p\n", sbrk(0));
	int * two = (int *)MALLOC(50);
	printf("Added second item: sbrk(0) = %p\n", sbrk(0));
	int * three = (int *)MALLOC(50);
	printf("Added third item: sbrk(0) = %p\n", sbrk(0));
	int * four = (int *)MALLOC(50);
	printf("Added fourth item: sbrk(0) = %p\n", sbrk(0));
	int * five = (int *)MALLOC(50);
	printf("Added fifth item: sbrk(0) = %p\n", sbrk(0));
	int * six = (int *)MALLOC(50);
	printf("Added sixth item: sbrk(0) = %p\n", sbrk(0));
	int * seven = (int *)MALLOC(50);
	printf("Added seventh item: sbrk(0) = %p\n", sbrk(0));
	int * eight = (int *)MALLOC(50);
	printf("Added eighth item: sbrk(0) = %p\n", sbrk(0));
	int * nine = (int *)MALLOC(50);
	printf("Added ninth item: sbrk(0) = %p\n", sbrk(0));
	int * ten = (int *)MALLOC(50);
	
	printf("After adding the tenth item of size 50 each, sbrk(0) = %p\n\n", sbrk(0));
	
	printf("Going to remove items from last to first (10-1). sbrk(0) should decrease each time.\n");
	
	FREE(ten);
	printf("After the tenth (last) item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(nine);
	printf("After the ninth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(eight);
	printf("After the eighth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(seven);
	printf("After the seventh item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(six);
	printf("After the sixth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(five);
	printf("After the fifth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(four);
	printf("After the fourth item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(three);
	printf("After the third item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(two);
	printf("After the second item is freed, sbrk(0) = %p\n", sbrk(0));
	FREE(one);
	printf("After the first item is freed, sbrk(0) = %p\n", sbrk(0));
	
}

void test4()
{
	printf("\nThis test will demonstrate the worst-fit implementation.\n");

	printf("\nInitial base is %p\n\n", sbrk(0));
	
	printf("Going to add ten items of size 50 each to the heap...\n");
	
	void * afterFive;
	
	int * one = (int *)MALLOC(50);
	printf("\nAdded first item: sbrk(0) = %p\n", sbrk(0));
	int * two = (int *)MALLOC(50);
	printf("Added second item: sbrk(0) = %p\n", sbrk(0));
	int * three = (int *)MALLOC(50);
	printf("Added third item: sbrk(0) = %p\n", sbrk(0));
	int * four = (int *)MALLOC(50);
	printf("Added fourth item: sbrk(0) = %p\n", sbrk(0));
	int * five = (int *)MALLOC(50);
	printf("Added fifth item: sbrk(0) = %p\n", sbrk(0));
	afterFive = sbrk(0);
	int * six = (int *)MALLOC(50);
	printf("Added sixth item: sbrk(0) = %p\n", sbrk(0));
	int * seven = (int *)MALLOC(50);
	printf("Added seventh item: sbrk(0) = %p\n", sbrk(0));
	int * eight = (int *)MALLOC(50);
	printf("Added eighth item: sbrk(0) = %p\n", sbrk(0));
	int * nine = (int *)MALLOC(50);
	printf("Added ninth item: sbrk(0) = %p\n", sbrk(0));
	int * ten = (int *)MALLOC(50);
	printf("After adding the tenth item of size 50 each, sbrk(0) = %p\n\n", sbrk(0));
	
	printf("Freeing items 2-4,and items 6-9. sbrk(0) should not change.\n");
	FREE(two);
	FREE(three);
	FREE(four);
	FREE(six);
	FREE(seven);
	FREE(eight);
	FREE(nine);
	
	printf("After freeing items 2-4 and items 6-9, sbrk(0) = %p\n", sbrk(0));
	
	printf("\nAllocating a new block of the size 50: it should be allocated where the sixth element was (ie. sbrk(0) after element 5 added plus size of node), at that is the largest open block.\n");
	six = (int *) MALLOC(50);
	
	FREE(six);
	FREE(one);
	FREE(five);
	FREE(ten);
	printf("\nAfter freeing the rest of the items, sbrk(0) = %p\n\n", sbrk(0));
	
}

int main()
{
//Write you own test code here!
//
//
	printf("\nTEST 1: -------------------------------------------\n");
	test1();
	
	printf("TEST 2: ------------------------------------------------------------\n");
	test2();
	
	printf("\nTEST 3: ------------------------------------------------------------\n");
	test3();
	
	printf("\nTEST 4: ------------------------------------------------------------\n");
	test4();

	return 0;
}
