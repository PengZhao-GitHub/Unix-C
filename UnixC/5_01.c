#include <unistd.h>

void main()
{
	int i=0;
	alarm(5);
	for(;;){
		printf("%d\n",++i);
		sleep(1);
	}
}
