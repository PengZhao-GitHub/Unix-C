#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void main(int argc, char* argv[])
{
	DIR *dirp;
	struct dirent *direntp;
	long loc;

	if (argc !=2) {
		fprintf(stderr,"Usage: %s directory_name\n",argv[0]);
		exit(1);
	}

	if ((dirp=opendir(argv[1])) == NULL) {
		fprintf(stderr,"Could not open %s direcotry: %s\n");
		exit(1);
	}

	while ((direntp=readdir(dirp)) != NULL) 
		printf("%s\n",direntp->d_name);

	printf("Rewind ...\n");
	
	rewinddir(dirp);


	while ((direntp=readdir(dirp)) != NULL) 
		printf("%s\n",direntp->d_name);


	rewinddir(dirp);
	printf("Tell the dir %ld\n",loc=telldir(dirp));

	printf("Seek forword 1 step\n");	
	seekdir(dirp,loc+1);

	while ((direntp=readdir(dirp)) != NULL) 
		printf("%s\n",direntp->d_name);

	close(dirp);

	exit(0);
}

