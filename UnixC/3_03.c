#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>


void main(int argc, char* argv[])
{
	struct stat statbuf;

	if (argc !=2) {
		fprintf(stderr,"Usage: %s directory_name\n",argv[0]);
		exit(1);
	}

	if (stat(argv[1],&statbuf) == -1) {
		fprintf(stderr,"Could not get stat on file %s: %s\n",
			argv[1], strerror(errno));
		exit(1);
	}

	if (statbuf.st_mode & S_IFDIR) {
		printf("%s is a directory: ", argv[1]);
		printf("last modified at %s\n",ctime(&statbuf.st_mtime));
	} else if (statbuf.st_mode & S_IFREG ) {
		printf("%s is a regular file: ", argv[1]);
		printf("File size is %ld\n", statbuf.st_size);
	}

	exit(0);
}

