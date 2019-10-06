/* 
POSIX.1b Named semaphore 
*/	

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(int argc, char* argv[])
{

	char buffer[MAX_CANON];
	char *c;
	
	int i,val;
	int n;
	int iRet;
	pid_t childpid;

	sem_t * semptr;

	if ( (argc!=2) || ((n=atoi(argv[1]))<=0) ) {
		fprintf(stderr, "Usage: %s number_of_process\n", argv[0]);
		exit(1);
	}

	sem_unlink("/mylocksem");

	semptr=sem_open("/mylocksem",O_CREAT|O_EXCL,S_IRWXU|S_IRWXG|S_IRWXO,1);
	if ( semptr == (sem_t *)-1) {
		perror("Could not initialize mylock semaphore");
		exit(1);
	}	

	for (i=1; i<n; ++i)
		if (childpid = fork())
			break;
	
	sem_getvalue(semptr,&val);
	printf("Waiting ... [Process ID %ld Mutex value is %d]\n", (long)getpid(),val);
	
	if ((iRet=sem_wait(semptr))== -1) {
		perror("semaphore invalid");
		exit(1);
	}
	sem_getvalue(semptr,&val);
	printf("Entering ... [Process ID %ld Mutex value is %d]\n", (long)getpid(),val);
	
	printf("Process ID %ld Parant ID %ld\n",(long) getpid(), (long)getppid());

	n=0;
	while(n<=4000){
		fputc(40+i,stderr);
		/*sleep(1);*/
		n++;	
	}

	fputc('\n',stderr);

	if (sem_post(semptr)== -1) {
		perror("semaphore done");
		exit(1);
	}

	sem_getvalue(semptr,&val);
	printf("Leaving ... [Process ID %ld Mutex value is %d]\n", (long)getpid(),val);

	sem_close(semptr);

	exit(0);

}
