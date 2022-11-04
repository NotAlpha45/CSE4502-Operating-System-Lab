#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("Child Process.\n");
        printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
    }
    else if (pid > 0)
    {
        printf("Parent Process.\n");
        printf("Process ID: %d\n", getpid());
    }
}