#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void main()
{
	int fd;
	char s[12];
	if ((fd=open("my.file", O_RDONLY))==-1)
		perror("Could not open the file my.file");
	else
	{
		if (dup2(fd,STDIN_FILENO) == -1)
			perror("Could not redirect standard in");
		close(fd);

		scanf("%s", s);
		printf("%s\n",s);
	}
	exit(0);
}
