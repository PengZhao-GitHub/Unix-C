#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	char *mycwdp;
	long maxpath;

	if ( (maxpath= pathconf("/",_PC_PATH_MAX)) == -1) {
		perror("Could not determine maximum pathname length");
		exit(1);
	} else if ((mycwdp = (char*) malloc(maxpath+1))==NULL) {
		perror("Could not allocate space for direcotry pathname");
		exit(1);
	} else if (getcwd(mycwdp,maxpath)==NULL) {
		perror("Could not get current working directory");
		exit(1);
	}

	printf("The MAX path length from \"/\" is %ld\n",maxpath);
	printf("Current working directory: %s\n", mycwdp);
	exit(0);
}
