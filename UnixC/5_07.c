#include <signal.h> 
#include <stdio.h>
#include <setjmp.h>

static volatile sig_atomic_t jumpok = 0;
static sigjmp_buf jmpbuf;

void int_handler(int signo)
{
	if (jumpok ==0) return ;
	printf("%d\n",signo);
	siglongjmp(jmpbuf,1);
}


void main()
{
	struct sigaction act;
	int i=0;

	act.sa_handler=int_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGINT,&act,NULL) <0 ) {
		perror("Could not install SIGINT handler");
		exit(1);
	}

	if (sigsetjmp(jmpbuf,1))
		fprintf(stderr,"returned to main loop due to ctrl-c\n");

	jumpok = 1;

	printf("I am here\n");
	for(;;)
	{
		/*printf("%d\n ",++i);*/
	}

}
