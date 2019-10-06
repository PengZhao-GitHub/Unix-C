#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

void main(int argc, char* argv[])
{
	char buffer[MAX_CANON];
	char *c;

	int i;
	int n;
	pid_t childpid;

	if ( (argc!=2) || ((n=atoi(argv[1]))<=0) ) {
		fprintf(stderr, "Usage: %s number_of_process\n", argv[0]);
		exit(1);
	}

	for (i=1; i<n; ++i)
		if (childpid = fork())
			break;

	n=0;
	while(n<=4000){
		fputc(40+i,stderr);
		/*sleep(1);*/
		n++;	
	}

	fputc('\n',stderr);

	exit(0);
}
		
