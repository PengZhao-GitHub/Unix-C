#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
	FILE* fp;
	unsigned char   fd;
	char buf[2];
	
	memset(buf,0,sizeof(buf));	

	if ((fd=open("my.file",O_RDONLY))== -1)
	{
		perror("Could not open my.file");
		exit(1);
	}

	if ( read(fd,buf,1) <= 0 ) 
	{
		perror("Could not read from my.file");
		exit(1);
	}

	printf("%s\n",buf);


}
