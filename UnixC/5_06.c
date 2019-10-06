#include <unistd.h>
#include <signal.h>


void hello(int signo)
{
	printf("alram!\n");
}

void main()
{
	int i=0;
	struct sigaction sigact;
	sigset_t set;
	sigset_t old;
	
	sigact.sa_handler = hello;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;

	if (sigaction(SIGALRM,&sigact,NULL) == -1)
		perror("Could not install SIGALARM handler");

	alarm(5);

	printf("Wait for SIGALRM...\n");

	sigprocmask(SIG_SETMASK,NULL,&set);
	sigaddset(&set,SIGALRM);
	sigprocmask(SIG_SETMASK,&set,NULL);
	sigdelset(&set,SIGALRM);

	sigsuspend(&set);

	printf("SIGALARM signal occured!\n");
	

}
