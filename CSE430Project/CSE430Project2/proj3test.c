/*
 * proj3test.c
 *
 *  Created on: Nov 12, 2015
 *      Author: sbmohan1
 */

#include "sem.h"

//global declarations
int global = 0;
int item = 1;
int buffout = 0;
int in = 0;
int out = 0;
int buff[5];
struct semaphore *sem;
struct semaphore *empty;
struct semaphore *full;

//forward method declarations
void producer1();
void producer2();
void consumer1();
void consumer2();
void mallocQueue();
void mallocSemaphore();
void initializeEmptyFull();


//first producer
void producer1()
{
	int i;

	for(;;)
	{
		int itemFree1 = 0;
		int itemFree2 = 0;
		P(empty);
		buff[in] = item;
		in = (in + 1) % 5;

		printf("Producer 1: Buffer free at location(s) ");

		//loop through buffer and find free spaces, then print
		for(i = 0; i < 5; i++)
		{
			if(buff[i] == 1)
			{
				if (i == 4)
				{
					printf("%d\n", i+1);
				}

				else
					printf("%d, ", i+1);
			}
			else
			{
				if (i == 4)
				{
					printf("\n");
				}
			}
		}

		V(full);
	}
}

//second producer
void producer2()
{
	int i;
	for(;;)
	{
		P(empty);
		buff[in] = item;
		in = (in + 1) % 5;
		printf("Producer 2: Buffer free at location(s) ");

		//loop through buffer and find free spaces, then print
		for(i = 0; i < 5; i++)
		{
			if(buff[i] == 1)
			{
				if (i == 4)
				{
					printf("%d\n", i+1);
				}

				else
					printf("%d, ", i+1);
			}
			else
			{
				if (i == 4)
				{
					printf("\n");
				}
			}
		}
		V(full);
	}
}

//first consumer
void consumer1()
{
	int i;
	for(;;)
	{
		P(full);
		buff[out] = buffout;
		out = (out + 1) % 5;
		//loop through buffer and find free spaces, then print
		printf("Consumer 1: Buffer free at location(s) ");
				for(i = 0; i < 5; i++)
				{
					if(buff[i] == 1)
					{
						if (i == 4)
						{
							printf("%d\n", i+1);
						}

						else
							printf("%d, ", i+1);
					}
					else
					{
						if (i == 4)
						{
							printf("\n");
						}
					}
				}
		V(empty);
	}
}

//second consumer
void consumer2()
{
	int i;
	for(;;)
	{
		P(full);
		buff[out] = buffout;
		out = (out + 1) % 5;
		printf("Consumer 2: Buffer free at location(s) ");
				for(i = 0; i < 5; i++)
				{
					if(buff[i] == 1)
					{
						if (i == 4)
						{
							printf("%d\n", i+1);
						}

						else
							printf("%d, ", i+1);
					}
					else
					{
						if (i == 4)
						{
							printf("\n");
						}
					}
				}
		V(empty);
	}
}


//method to allocate memory for the runQueue
void mallocQueue()
{
	runQueue = (struct queues*) malloc(sizeof(struct queues));
}

//method to allocate memory for the Semaphore structs
void mallocSemaphore()
{
	empty = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	full = (struct Semaphore*) malloc(sizeof(struct Semaphore));
}

//method to initialize the semaphore to empty and a semaphore to full
void initializeEmptyFull()
{
	InitSem(5, empty);
	InitSem(0, full);
}


int main()
{
	//call methods to set up semaphores and the RunQueue
	mallocQueue();
	mallocSemaphore();
	initializeEmptyFull();
	InitQueue(runQueue);

	//initialize buffer which is an int array
	buff[0] = 0;
	buff[1] = 0;
	buff[2] = 0;
	buff[3] = 0;
	buff[4] = 0;

	//start threads
	start_thread(consumer1);
	start_thread(producer1);
	start_thread(consumer2);
	start_thread(producer2);

	run();

	return 0;
}
