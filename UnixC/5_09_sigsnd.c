#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void main(int argc, char* argv[])
{
	int pid;
	int signo;

	if (argc != 3) {
		fprintf(stderr,"Usage:%s pid signal \n",argv[0]);
		exit(1);
	}

	pid = atoi(argv[1]);
	signo = atoi(argv[2]);

	fprintf(stderr,"Sending signal %d to process %d\n", signo,pid);


	kill(pid,signo);

}

