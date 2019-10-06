#include <unistd.h>
#include <signal.h>


void hello(int no)
{
	static int i=0;
	if (no == SIGALRM)
	{
		printf("alarm! signal no.%d\n",no);
		alarm(++i);
	}
		
	if (no == SIGINT )
		printf("Got Crtl-c\n");
}

void main()
{
	int i=0;
	struct sigaction newact;

	newact.sa_handler = hello; 
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;

	if ( sigaction(SIGALRM,&newact,NULL) == -1 )
		perror("Could not install SIGALRM handler");

	if ( sigaction(SIGINT,&newact,NULL) == -1 )
		perror("Could not install SIGALRM handler");
	
	alarm(1);
	for(;;){
		printf("%d\n",++i);
		sleep(1);
	}
}
