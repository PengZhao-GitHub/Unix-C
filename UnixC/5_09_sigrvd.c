#include <signal.h> 
#include <stdio.h>
#include <setjmp.h>

static volatile sig_atomic_t jumpok = 0;
static sigjmp_buf jmpbuf;

void int_handler(int signo)
{
	static int i=0;
	i++;
	printf("sighandler: signo= %d\n",signo );

	if (i == 3)
		exit(0);

}

void main()
{
	struct sigaction act,almact;
	long i=0;
	sigset_t mysigset;

	sigemptyset(&mysigset);
	sigaddset(&mysigset,SIGINT);
	sigprocmask(SIG_BLOCK,&mysigset,NULL);

	act.sa_handler=int_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGINT,&act,NULL) <0 ) {
		perror("Could not install SIGINT handler");
		exit(1);
	}

	for(;;)
	{
		if (i<  599999) printf("%ld\n",++i);
		if (i== 599999)
			sigprocmask(SIG_UNBLOCK,&mysigset,NULL);
	}

}
