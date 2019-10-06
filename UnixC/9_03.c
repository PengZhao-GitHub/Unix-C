#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>

pthread_attr_t my_tattr;

pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;

void threadInfo(void *arg);

void main(int argc, char* argv[])
{
	size_t st;
	pthread_t *tid;
	int threadCount;

	int i;

	int *a;
	 
	/* parameter check */
	/*******************/	
	if (argc<2) {
		fprintf(stderr,"usage: %s <thread numbers>\n",argv[0]);
		exit(1);	
	}

	threadCount = atoi(argv[1]);

	if (threadCount <=0) {
		fprintf(stderr,"thread numbers must be a negative integer!\n");
		exit(1);
	}		


	/* Create thread paramenter array */
	/**********************************/
	if ( (a = (int*)calloc(threadCount,sizeof(int))) == NULL) {
		fprintf(stderr,"Could not alloc memory for thread return value\n");
		exit(1);
	}

	for (i=0; i<threadCount; i++)
		a[i]=i;


	/* Create thread identifier array */
	/**********************************/
	if ( (tid = (pthread_t*)calloc(threadCount,sizeof(pthread_t))) == NULL ) {
		fprintf(stderr,"Could not alloc memory for pthread_t structure\n");
		exit(1);
	}

	/* Init thread attribute structure and set new attribute */ 
	if (pthread_attr_init(&my_tattr)) {
		perror("Could not init thread attribute structure");
		return;
	}	

	if (pthread_attr_setstacksize(&my_tattr,6000)){
		perror("Could not get the statck size of this thread");
		return;
	}
	/*
	if (pthread_attr_setscope(&my_tattr,PTHREAD_SCOPE_SYSTEM)) {
		perror("Could not set the scope of this thread");
		return;
	}
	*/


	/* Create threads */
	/******************/
	for (i=0;i<threadCount;i++) {
		if (pthread_create((tid+i),NULL,threadInfo,(void*)(a+i))) {
			fprintf(stderr,"Could not create thread %i: %s\n",i, strerror(errno));
			exit(1);
		}
	}	


	/* Wait for all threads to end */
	/*******************************/
	for (i=0; i<threadCount;i++)
		pthread_join(*(tid+i),NULL);
	

	printf("End of the main thread\n");

	exit(0);

}


void threadInfo(void *arg)
{
	int j,*count;

	count = (int*)(arg);

	/* lock the critical region */
	/****************************/
	pthread_mutex_lock(&my_lock);

	fprintf(stderr,"thread %ld enter the  critical region\n",pthread_self());

	for (j=0; j<=2; j++)
	{
		fputc((char)('0'+ *count),stderr);
		sleep(1);	
	}
	fputc('\n',stderr);	
	
	fprintf(stderr,"thread %ld leaving the  critical region\n",pthread_self());
	/* unlock the critical region */
	/****************************/
	pthread_mutex_unlock(&my_lock);
	
	return;
}

