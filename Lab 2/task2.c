#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>	   /* Standard I/O functions */
#include <stdlib.h>	   /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>	   /* Prototypes for many system calls */
#include <errno.h>	   /* Declares errno and defines error constants */
#include <string.h>	   /* Commonly used string-handling functions */
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid1;
	int n;

	pid1 = fork();

	if (pid1 == 0)
	{
		printf("Child Process\n");
		scanf("%d", &n);
		if (n % 2 == 0)
		{
			n += 1;
		}
		printf("5 odd numbers: ");
		for (int i = 0; i < 5; i++)
		{
			printf("%d ", n);
			n += 2;
		}
		printf("\n");
	}
	else if (pid1 > 0)
	{
		wait(NULL);
		printf("Parent Process\n");
		scanf("%d", &n);
		if (n % 2 != 0)
		{
			n += 1;
		}
		printf("5 even numbers: ");
		for (int i = 0; i < 5; i++)
		{
			printf("%d ", n);
			n += 2;
		}
		printf("\n");
	}
}
