/* 
POSIX.1b Unnamed  semaphore
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

struct shared {
	sem_t mutex;
	int   cout;
} shared;

void main(int argc, char* argv[])
{
	char buffer[MAX_CANON];
	char *c;
	
	int i,val;
	int n;
	int iRet;
	pid_t childpid;

	int fd;
	struct shared *ptr;


	if ( (argc!=2) || ((n=atoi(argv[1]))<=0) ) {
		fprintf(stderr, "Usage: %s number_of_process\n", argv[0]);
		exit(1);
	}

	fd = open("./mutex",O_RDWR|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO);
	write(fd,(char*)&shared, sizeof(struct shared));
	ptr = mmap(	NULL, 
				sizeof(struct shared), 
				PROT_READ|PROT_WRITE,
				MAP_SHARED,
				fd,
				0);
	close(fd);
	
	if (sem_init(&ptr->mutex,1,1)==-1) {
		perror("Could not initialize mylock semaphore");
		exit(1);
	}	

	for (i=1; i<n; ++i)
		if (childpid = fork())
			break;
	
	sem_getvalue(&ptr->mutex,&val);
	printf("Waiting ... [Process ID %ld Mutex value is %d]\n", (long)getpid(),val);
	
	if ((iRet=sem_wait(&ptr->mutex))== -1) {
		perror("semaphore invalid");
		exit(1);
	}
	sem_getvalue(&ptr->mutex,&val);
	printf("Entering ... [Process ID %ld Mutex value is %d]\n", (long)getpid(),val);
	
	printf("Process ID %ld Parant ID %ld\n",(long) getpid(), (long)getppid());

	n=0;
	while(n<=4000){
		fputc(40+i,stderr);
		/*sleep(1);*/
		n++;	
	}

	fputc('\n',stderr);

	if (sem_post(&ptr->mutex)== -1) {
		perror("semaphore done");
		exit(1);
	}

	sem_getvalue(&ptr->mutex,&val);
	printf("Leaving ... [Process ID %ld Mutex value is %d]\n", (long)getpid(),val);
		
	exit(0);

}
