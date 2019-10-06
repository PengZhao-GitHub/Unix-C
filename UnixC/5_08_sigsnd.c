#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void main(int argc, char* argv[])
{
	union sigval qval;
	int val;
	int pid;
	int signo;

	if (argc != 4) {
		fprintf(stderr,"Usage:%s pid signal value\n",argv[0]);
		exit(1);
	}

	pid = atoi(argv[1]);
	signo = atoi(argv[2]);
	val = atoi(argv[3]);

	fprintf(stderr,"Sending signal %d whith value %d to process %d\n", signo,val,pid);

	qval.sival_int = val;

	sigqueue(pid,signo,qval);

}

