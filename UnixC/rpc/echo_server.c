/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "echo.h"
#include <stdio.h>
#include <stdlib.h> /* getenv, exit */
#include <signal.h>

int *
add_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	result=*argp*10;

	return (&result);
}