#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdll.h"

/* just a convenience */
void fatal( char * msg )
{
	printf("%s\n",msg);
	exit(EXIT_FAILURE);
}


/* ----------------------------------------------------------------------------
	initList: Initialize the linked list functions and set head to NULL.
*/
void initList(CDLL *list, int (*compare)(void*, void*), void (*print)(void*, int),
			  void (*freeData)(void *))
{
	list->head=NULL;
	list->compare=compare;
	list->print=print;
	list->freeData=freeData;
}


/* ----------------------------------------------------------------------------
    insertAtTail: Insert a node at the end of the Linked List list with Data data.
*/
void insertAtTail(CDLL *list, void *data)
{
	CDLL_NODE * node = malloc(sizeof(CDLL_NODE));

	if(!list->head) //if the Linked List head is Null then set up the first node
    	{
        	node->data=data;
        	node->prev=node;
        	node->next=node;
        	list->head=node;
    	}
	else    //else insert the node at the end of the Linked List
    	{
        	CDLL_NODE * oldTail = list->head->prev;
        	node->data=data;
        	node->prev=oldTail;
        	node->next=list->head;
        	list->head->prev=node;
        	oldTail->next=node;
    	}

}


/* ----------------------------------------------------------------------------
	deleteNode: Remove Node deadNode from Linked List list and returns deadNodes previous node.
       		    If CW then return deadNode's successor, and if CCW then return deadNode's predecessor.
*/
CDLL_NODE * deleteNode(CDLL *list, CDLL_NODE *deadNode, int direction )
{
	if(list == NULL)    //if list pointer NULL then return -1 for error
    	{
        	return -1;
    	}

	CDLL_NODE * prev = deadNode->prev;
	CDLL_NODE * next = deadNode->next;

	prev->next = next;
	next->prev = prev;

	if(deadNode == list->head)    //if deadNode is the head then set list head to next
    	{
        	list->head = next;
    	}

    	list->freeData(deadNode->data); //free the data using our freeData function
    	free(deadNode); //free deadNode

    	if(prev == deadNode && next == deadNode)    //if deadNode is the only node then set head to null and return null
    	{
        	list->head = NULL;
        	return NULL;
    	}
    	else if(direction == CLOCKWISE) //if direction is CLOCKWISE return next node
    	{
        	return next;
    	}
    	else    //else if direction is COUNTERCLOCKWISE return previous node
    	{
        	return prev;
    	}
}


/* ----------------------------------------------------------------------------
	printList: Loop through the list and call list.print(data,mode); on each node
*/

void printList( CDLL list, int direction, int mode )
{
	direction=direction;    //just to prevent compiler from yelling non used parameter
	CDLL_NODE * cur=list.head;
	list.print(cur->data,mode);
	cur=cur->next;
	while(cur != list.head) //while were not back and the beginning of the linked list
    	{
        	list.print(cur->data,mode); //print node
        	cur=cur->next;
    	}
    	printf("\n");
}


/* ----------------------------------------------------------------------------
	searchList: Scan the Linked List until you find the node that contains
                the value target.  If not found return NULL
*/
CDLL_NODE * searchList( CDLL list, void * target )
{
	CDLL_NODE * head = list.head;
	if(list.compare(target,head->data)==0)  //check if target is head
    	{
        	return head;
    	}

    	CDLL_NODE * cur = head->next;
    	while(cur != head)  //while were not back at head
    	{
        	if(list.compare(target,cur->data)==0)   //if target == cur->data then return cur
        	{
            		return cur;
        	}
        	cur = cur->next;    //increment cur
    	}

    	return NULL; //if not found return NULL
}
