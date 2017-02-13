/*
 * sem.h
 *
 *  Created on: Nov 12, 2015
 *      Author: password
 */

#ifndef SEM_H_
#define SEM_H_
#include "threads.h"

struct Semaphore
{
	struct queues *queueTCB;
	int value;
};

//declare struct of Semaphore
struct Semaphore semaphore;

void P(struct Semaphore * semaphore); //wait
void V(struct Semaphore * semaphore); //signal
void InitSem(int value, struct Semaphore * semaphore);

void P(struct Semaphore * semaphore)
{


	//set value and decrement
	int value = semaphore->value;
	value--;
	semaphore->value = value;

	//if value is less than 0 then blocks the process in the queue
	//associated with the semaphore
	if (value < 0)
	{
		struct TCB_t *tcb = DelQueue(runQueue);
		AddQueue(semaphore->queueTCB, tcb);
		swapcontext(&(tcb->context), &(runQueue->first_element->context)); //swap context
	}

}

void V(struct Semaphore *semaphore)
{

	//set value and increment
	int value = semaphore->value;
	value++;
	semaphore->value = value;


	//if value is 0 or negative, then takes a PCB out of the semaphore queue
	//and puts it in run queue
	if (value <= 0)
	{
		struct TCB_t *tcb = DelQueue(semaphore->queueTCB);
		AddQueue(runQueue, tcb);
	}

	yield(); //yields to next runnable process - this is important
}

void InitSem(int value, struct Semaphore * semaphore)
{
	struct queues *qTCB;
	qTCB = (struct queues*) malloc(sizeof(struct queues));
	semaphore->queueTCB = qTCB;
	//semaphore->value = valueParam;

	//value has to be set after initialization of the queue
	InitQueue(qTCB);
	int valueParam = value;
	semaphore->value = valueParam;

}
#endif /* SEM_H_ */
