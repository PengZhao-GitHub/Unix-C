#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>

pthread_attr_t my_tattr;

void threadInfo();

	pthread_attr_t my_tattr;
void main(int argc, char* argv[])
{
	size_t st;
	pthread_t *tid;
	int threadCount;
	int i;


	if (argc<2) {
		fprintf(stderr,"usage: %s <thread numbers>\n",argv[0]);
		exit(1);	
	}

	threadCount = atoi(argv[1]);

	if (threadCount <=0) {
		fprintf(stderr,"thread numbers must be a negative integer!\n");
		exit(1);
	}		

	if ( (tid = (pthread_t*)calloc(threadCount,sizeof(pthread_t))) == NULL ) {
		fprintf(stderr,"Could not alloc memory for pthread_t structure\n");
		exit(1);
	}
	
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

	for (i=0;i<threadCount;i++) {
		if (pthread_create((tid+i),NULL,threadInfo,NULL)) {
			fprintf(stderr,"Could not create thread %i: %s\n",i, strerror(errno));
			exit(1);
		}
	}	

	
	for (i=0; i<threadCount;i++)
		pthread_join(*(tid+i),NULL);

	
	if (pthread_attr_getstacksize(&my_tattr,&st)){
		perror("Could not get the statck size of this thread");
		return;
	}

	printf("%ld,%ld\n",pthread_self(),st);
	printf("End of the main thread\n");


	getchar();

	exit(0);

}


void threadInfo(void *arg)
{
	size_t st;

	st = -1;
	if (pthread_attr_getstacksize(&my_tattr,&st)){
		perror("Could not get the statck size of this thread");
		return;
	}

	printf("%ld,%ld\n",pthread_self(),st);
	
	getchar();

	return;
}

