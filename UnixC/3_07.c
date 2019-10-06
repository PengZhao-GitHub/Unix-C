#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main()
{

	int fd;
	mode_t fd_mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;

	if ( (fd=open("my.file",O_WRONLY|O_CREAT, fd_mode)) == -1)
	{
		perror("Could not open my.file");
		exit(1);	
	}	
	else{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("Could not redirect standard output");
		
		close(fd);
	}

	/* if(unlink("./my.file"))
	{
			perror("Could not unlink the file");
			exit(1);
	}*/

	printf("Hello");
	printf(" world\n");

	exit(0);

}
