#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
	pid_t childpid;
	int status;

	fork();
	if ((childpid=fork())==-1)
		perror("The fork failed");
	else if (childpid ==0)
	{
		printf("I am the child with pid %ld\n",(long)getpid());
		sleep(20);	
	}	
	else if ( childpid != wait(&status))
		printf("A signal must have interrupted the wait\n");
	else  printf("I am the parent with pid %ld and child pid %ld\n",
		(long)getpid(), (long)childpid);
}

