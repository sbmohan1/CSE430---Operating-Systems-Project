#ifndef Q_H_
#define Q_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcb.h"


struct queues {
	struct TCB_t *first_element;
};



struct TCB_t * NewItem();
void InitQueue(struct queues *head);
void AddQueue(struct queues *head, struct TCB_t * item);
struct TCB_t* DelQueue(struct queues *head);
void RotateQ(struct queues *head);
void QueueView();

// Global variables
//struct TCB_t *head;
//struct TCB_t *tail;




void QueueView(struct queues *head)
{
	struct TCB_t* printItem;
	int count;
	printItem = head->first_element;

	if (printItem == NULL)
	{
		printf("\nThere are no TCB_ts to display.\n");
	}

	count = 0;

	while (printItem != NULL && count < 30)
	{
		count++;
		printf("Item %d\n", printItem->context);
		printItem = printItem->next;
	}


}

struct TCB_t * NewItem()
{
	struct TCB_t *newitem = (struct TCB_t *) malloc(sizeof(struct TCB_t));
	
	// Initialize
	//newitem->context = NULL;
	newitem->next = NULL;
	newitem->previous = NULL;

	return newitem;
}

void InitQueue(struct queues *head)
{
	head->first_element = NULL;
}

void AddQueue(struct queues *head, struct TCB_t* item)
{
	struct TCB_t *temp;
	temp = (struct TCB_t *) malloc(sizeof(struct TCB_t));

	// Case 1: no elements
	if(head->first_element == NULL)
	{
		head->first_element = item;
		item->previous = NULL;
		item->next = NULL;
	}

	// Case 2: list has 1 element
	else if (head->first_element->next == NULL)
	{
		head->first_element->next = item;
		head->first_element->previous = item;
		item->next = head->first_element;
		item->previous = head->first_element;
	}

	// Case 3: list has 2 element
	else
	{

		item->previous = head->first_element->previous;
		item->next = head->first_element;
		head->first_element->previous->next = item;
		head->first_element->previous = item;

		
	}


}

struct TCB_t* DelQueue(struct queues *head)
{
	struct TCB_t *itemToDelete;
	itemToDelete = head->first_element;

	if (head == NULL) //nothing in queue
	{
		//return;
	}

	if (head->first_element->next == NULL)//one item in queue
	{	
		head = NULL;
	}
	else //multiple items in queue
	{
		head->first_element->previous->next = head->first_element->next;
		head->first_element->next->previous = head->first_element->previous;
		head->first_element = head->first_element->next;

	}

	return itemToDelete;
}


void RotateQ(struct queues *head)
{
	AddQueue(head, DelQueue(head));
	
}

#endif
