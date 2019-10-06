#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <curses.h>

void main()
{
	int fd[2];
	pid_t childpid;
	char s;
	char buf[2];
	int fd_flags;

	memset(buf,0,sizeof(buf));

	if (pipe(fd)) {
		perror("Could not create pipe");
		exit(0);
	}

	if ((childpid=fork()) == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		while((s=getchar())!='!')
			putchar(s);

		putchar('!');	

	} else {
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		printf("Father begin...\n");	
	
		if ((fd_flags=fcntl(STDIN_FILENO,F_GETFL,0))==-1)
				perror("Could not get flags for fd");
		else {
				printf("Get it!\n");
				fd_flags |= O_NONBLOCK;
				if (fcntl(STDIN_FILENO,F_SETFL,fd_flags)==-1)
					perror("Could not set flags for STDIN_FILENO");
		}
		
		while(1)
		{
			if (read(STDIN_FILENO,buf,1)<=0)
				continue;	
		
			printf("This is father: %s\n",buf);
			break;
		}

		printf("Father end...\n");	
		
		getchar();
	}

	exit(0);
}

		

