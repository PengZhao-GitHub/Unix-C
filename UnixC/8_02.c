/* 
The problem with this program is that the semaphore is not actually shared by those processes 
Please refer to 8_3.c which correct the problem. I do not know why the autors of this book 
made such mistake or there must be something I do not know. Mybe I should ask them.
*/ 


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <semaphore.h>

void main(int argc, char* argv[])
{
	char buffer[MAX_CANON];
	char *c;

	int i;
	int n;
	int iRet;
	pid_t childpid;
	sem_t my_lock;
	int val	=	0;
	
	if ( (argc!=2) || ((n=atoi(argv[1]))<=0) ) {
		fprintf(stderr, "Usage: %s number_of_process\n", argv[0]);
		exit(1);
	}

	if (sem_init(&my_lock,2,0)==-1) {
		perror("Could not initialize mylock semaphore");
		exit(1);
	}	

	for (i=1; i<n; ++i)
		if (childpid = fork())
			break;
	
	if (sem_post(&my_lock)== -1) {
			perror("semaphore done");
			exit(1);
	}
	

	if ((iRet=sem_wait(&my_lock))== -1) {
		perror("semaphore invalid");
		exit(1);
	}

	printf("wait result %d\n",iRet);

	n=0;
	while(n<=4000){
		fputc(40+i,stderr);
		/*sleep(1);*/
		n++;	
	}

	fputc('\n',stderr);

	if (sem_post(&my_lock)== -1) {
		perror("semaphore done");
		exit(1);
	}

	if (i==1){
		if (sem_post(&my_lock)== -1) {
			perror("semaphore done");
			exit(1);
		}	
	}
	
	
	if (sem_getvalue(&my_lock, &val)== -1) {
		perror("semaphore done");
		exit(1);
	}
	printf("value=[%d]\n",val);
		
	exit(0);

}
