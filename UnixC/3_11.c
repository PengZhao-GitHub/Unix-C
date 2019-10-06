#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
	FILE* fp;
	unsigned char   fd,fdnew;
	char buf[2];
	
	memset(buf,0,sizeof(buf));	

	if ((fp=fopen("my.file","r"))== NULL)
	{
		perror("Could not open my.file");
		exit(1);
	}

	if ( fread(buf,sizeof(char),1,fp) <= 0 ) 
	{
		perror("Could not read from my.file");
	}

	printf("%s\n",buf);
	
	fd =  fileno(fp);	
	fdnew = dup(fd);

	printf("file descriptor:%ld\n",fdnew);
	
	if ( read(fdnew,buf,1) <= 0 )
	{
		perror("Could not read from my.file");
	}
	printf("%s\n",buf);

}
