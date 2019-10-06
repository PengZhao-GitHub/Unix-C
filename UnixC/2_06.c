#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

main()
{
	int i;
	int n=5;
	pid_t childpid;
	int status;
	pid_t waitreturn;

	for(i=1; i<n; i++)
	{
		if (childpid=fork())
			break;
	}

	while(childpid != (waitreturn = wait(&status)))
		if ((waitreturn == -1) && (errno!=EINTR))
			break;

	fprintf(stderr, "I am process %ld, my parent is %ld\n",
		(long)getpid(), (long)getppid());
}
	

