#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int a=100;
main()
{
	int i;
	pid_t childpid;

	for ( i = 1; i<= 5; i++ )
	{
		if ((childpid=fork())<= 0)
			break;
	}

	fprintf(stderr,"This is process %ld with parent %ld\n",
		(long)getpid(),(long)getppid());

	sleep(20);
}
