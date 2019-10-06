#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PERMS S_IRUSR|S_IWUSR
#define SET_SIZE 3

void main()
{
	int semid;
	if (( semid = semget(IPC_PRIVATE, SET_SIZE, PERMS)) <0)
		perror("Could not create new private semaphore");

	getchar();
}
