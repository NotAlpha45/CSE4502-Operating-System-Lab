#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>	   /* Standard I/O functions */
#include <stdlib.h>	   /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>	   /* Prototypes for many system calls */
#include <errno.h>	   /* Declares errno and defines error constants */
#include <string.h>	   /* Commonly used string-handling functions */
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid1, pid2, pid3;

	pid1 = fork();

	if (pid1 == 0)
	{
		printf("Child Process, parent:%d, process:%d\n", getpid(), getppid());
	}

	if (pid1 > 0)
	{
		wait(NULL);
		printf("Parent process %d \n", pid1);
		pid2 = fork();
	}

	if (pid2 == 0)
	{
		printf("Child Process, parent:%d, process:%d\n", getpid(), getppid());
	}

	if (pid2 > 0)
	{
		printf("Parent process %d \n", pid2);
		wait(NULL);
	}

	pid3 = fork();
	if (pid3 == 0)
	{
		printf("Child Process, parent:%d, process:%d\n", getpid(), getppid());
	}

	if (pid3 > 0)
	{
		wait(NULL);
		printf("Parent process %d \n", pid3);
	}
}
