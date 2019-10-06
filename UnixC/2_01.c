/************************************************************************/
/* Chapter 2 Process	2_01.c											*/
/* **********************************************************************/
/* NOTE: This programm show how to get the process ID and				*/
/*       Process's parent ID.											*/
/************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
	int i;
	int n=5;
	
	pid_t childpid;

	for( i = 1; i < n; ++i )
		if (childpid = fork())
			break;

	fprintf(stderr,"This is process %ld with parent %ld\n",
			(long)getpid(),(long)getppid());

	sleep(10);
}
