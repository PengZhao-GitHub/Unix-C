#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
	int myfd;
	pid_t childpid;
	char a[10];
	memset(a, 0, sizeof(a));
	if ((myfd=open("my.dat",O_RDONLY)) == -1)
		perror("Could not open file");
	else if ((childpid=fork()) == -1)
		perror("Could not fork");
	else if (childpid ==0)
	{
			read(myfd,a,1);
			printf("child read %s\n",a);
	}
	else {
			read(myfd,a,1);
			printf("father read %s\n",a);
	}
}
