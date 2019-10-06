#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void show1()
{
	printf("Exit program 1\n");
}

static void show2()
{
	printf("Exit program 2\n");
}

static void show3()
{
	printf("Exit program 3\n");
}

main()
{
	if (atexit(show1)) {
		printf("Cannot install show()\n");
		exit(1);
	}
	if (atexit(show2)) {
		printf("Cannot install show()\n");
		exit(1);
	}
	if (atexit(show3)) {
		printf("Cannot install show()\n");
		exit(1);
	}
	
	printf("Press return exit the program:");
	getchar();
	
	abort();

}
