/* single consumer and single producer problem */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sched.h>

#define SUMSIZE 100
#define BUFSIZE 8

static int buffer[BUFSIZE];
static int bufin = 0;
static int bufout =0;
static pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;

int sum=0;

void get_item(int *itemp)
{
	pthread_mutex_lock(&buffer_lock);
	*itemp = buffer[bufout];
	bufout = (bufout +1) % BUFSIZE;
	pthread_mutex_unlock(&buffer_lock);

	return;
}

void put_item(int item)
{
	pthread_mutex_lock(&buffer_lock);
	buffer[bufin] = item;
	bufin = (bufin +1) % BUFSIZE;
	pthread_mutex_unlock(&buffer_lock);

	return;
}

void *producer(void * arg1)
{
	int i;
	for (i=1; i<= SUMSIZE ; i++)
	{
		put_item(i);
		sched_yield();
	}
	return NULL;

}

void *consumer(void * arg2)
{
	int i, myitem;
	for (i=1; i<=SUMSIZE; i++) {
		get_item(&myitem);
		sum += myitem;
		sched_yield();
	}
	return NULL;
}

void main(void)
{
	pthread_t prodtid;
	pthread_t constid;
	
	int i;
	int total = 0;

	for (i = 0; i < BUFSIZE; i++ )
		buffer[i]=0;

	for (i=1; i<=SUMSIZE; i++)
		total +=i;

	printf("The actual sum should be %d\n",total);

	if (pthread_create(&constid, NULL, producer, NULL))
		perror("Could not create consumer");
	else if (pthread_create(&prodtid,NULL,consumer,NULL))
		perror("Could not create producer");
	
	/*
	if (pthread_create(&constid, NULL, consumer, NULL))
		perror("Could not create consumer");
	else if (pthread_create(&prodtid,NULL,producer,NULL))
		perror("Could not create producer");
	*/	
	pthread_join(prodtid,NULL);
	pthread_join(constid,NULL);

	printf("The threads procued the sum %d \n",sum);

	exit(0);
}
	



