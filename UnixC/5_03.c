#include <unistd.h>
#include <signal.h>

void main()
{
	int i=0;
    sigset_t towsigs;

	sigemptyset(&towsigs);
    sigaddset(&towsigs,SIGALRM);
	

	if (sigprocmask(SIG_BLOCK,&towsigs,NULL)<0)
		perror("Could not block the signal");

	alarm(1);
	
	for(;;){
		printf("%d\n",++i);
		/*sleep(1);*/
		if (i==65535)		
			sigprocmask(SIG_UNBLOCK,&towsigs,NULL);
	}
}
