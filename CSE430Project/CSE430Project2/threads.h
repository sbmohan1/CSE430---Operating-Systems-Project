/*
 * threads.h
 *
 *  Created on: Oct 31, 2015
 *      Author: sbmohan1
 */

#ifndef THREADS_H_
#define THREADS_H_
#include "q.h"

#define STACKSIZE 8192

struct queues *runQueue;

void run()
{
	ucontext_t parent;
	getcontext(&parent); //magic sauce
	swapcontext(&parent, &(runQueue->first_element->context));

	return;

}

void start_thread(void (*function) (void))
{
	void *stack = (void *) malloc(STACKSIZE);
	TCB_t * tcb = NewItem();
	init_TCB(tcb, function, stack, STACKSIZE);
	AddQueue(runQueue, tcb);

}

void yield()
{
	RotateQ(runQueue);
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQueue->first_element->context));

	return;
}
#endif
