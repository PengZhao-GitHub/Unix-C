#include <stdio.h>
#include <stdlib.h>

extern char **environ;

main()
{
	int i;

	for (i = 0; environ[i]!=NULL; i++)
		printf("%s\n",environ[i]);


	putenv("PENGZHAO=HELLO");

	for (i = 0; environ[i]!=NULL; i++)
		printf("%s\n",environ[i]);

}
