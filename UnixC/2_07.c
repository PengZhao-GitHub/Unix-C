#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
	pid_t childpid;
	int status;

	if ((childpid = fork()) == -1)
	{	
		perror("Error in the fork");
		exit(1);
	} else if (childpid == 0) {
		if (execl("/usr/bin/ls","ls","-l",NULL)<0 ) {
			perror("Exec of ls failed");
			exit(1);
		}
	} else if (childpid != wait(&status))
		perror("A signal occurred before the child exited");

	exit(0);
}



