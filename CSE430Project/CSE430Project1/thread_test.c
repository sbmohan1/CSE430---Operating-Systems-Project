/*
 * threads_test.c
 *
 *  Created on: Oct 31, 2015
 *      Author: sbmohan1
 */

#include "threads.h"


int global = 0; //counter to signify which thread is running


void thread1()
{
	while(1)
	{
		printf("This is thread 1 with global variable: \t%d\n", global);
		global++;

		yield();
	}

	return;
}

void thread2()
{
	while(1)
	{
		printf("This is thread 2 with global variable: \t%d\n", global);
		global = global * 2;

		yield();
	}
	return;
}


void thread3()
{
	while(1)
	{
		printf("This is thread 3 with global variable: \t%d\n", global);
		global = global * 10;

		yield();
	}
	return;
}

void thread4()
{
	while(1)
	{
		printf("This is thread 4 with global variable: \t%d\n", global);
		global = global * 20;

		yield();
	}
	return;
}



void main() {


	runQueue = (struct queues*) malloc(sizeof(struct queues));

	InitQueue(runQueue);

	start_thread(thread1);
	start_thread(thread2);
	start_thread(thread3);
	start_thread(thread4);
	run();
}



