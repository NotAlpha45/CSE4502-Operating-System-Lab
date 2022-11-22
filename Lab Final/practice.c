#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

#define newline printf("\n")

int process_worker(int id, int parent_id, char *action)
{
    printf("I am process: %d, I am doing %s\n", id, action);
    printf("My parent is %d", parent_id);
    newline;

    // Exit after doing the process
    exit(0);
}

int main()
{
    int no_of_process = 4;
    pid_t pid_array[4];

    printf("Start of parent process, %d", getpid());
    newline;

    for (int i = 0; i < no_of_process; i++)
    {
        pid_t current_process = fork();

        if (current_process == 0)
        {
            pid_array[i] = current_process;
            process_worker(getpid(), getppid(), "a random task");
        }
    }

    // Wait for all the child process to complete
    for (int i = 0; i < no_of_process; i++)
    {
        wait(&pid_array[i]);
    }

    printf("End of parent process\n");

    return 0;
}