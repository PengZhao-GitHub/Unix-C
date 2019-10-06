#include <unistd.h>
#include <signal.h>

int signal_received = 0;

void hello(int signo)
{
	signal_received = 1;
	printf("alram!\n");
}

void main()
{
	int i=0;
	struct sigaction sigact;

	sigact.sa_handler = hello;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;

	if (sigaction(SIGALRM,&sigact,NULL) == -1)
		perror("Could not install SIGALARM handler");

	alarm(5);

	if (signal_received == 0)
	{
		printf("pause the program until the SIGALRM  occur\n"); 
		pause();
	}	
		
	printf("SIGALARM signal occured!\n");
	

}
