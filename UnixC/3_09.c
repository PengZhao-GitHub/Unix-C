#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
	int fd[2];
	pid_t childpid;
	char s[255];

	if (pipe(fd)) {
		perror("Could not create pipe");
		exit(0);
	}

	if ((childpid=fork()) == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		printf("Hello this from child !");
	} else {
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	
		do { 
			scanf("%s",s);
			printf("This is father: %s\n",s);
		} while (s[0] != '!');	
	}

	exit(0);
}

		

