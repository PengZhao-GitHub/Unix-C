#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
	int i;
	int j;
	pid_t childpid;

	for ( i = 1; i < 4; i++ )
	{
		if ((childpid=fork()) == -1)
		{
			break;
		}			
	}
	
	fprintf(stdout,"This is process %ld with parent %ld\n",
	  (long)getpid(), (long)getppid());
}	
