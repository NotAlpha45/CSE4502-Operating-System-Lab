#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>
#include <math.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child Process\n");
        int n;
        while (1)
        {
            scanf("%d", &n);

            if (n <= 0)
            {
                printf("Please input a positive number");
            }
            else
            {
                break;
            }
        }
        printf("The fist %d square integer numbers: ", n);
        for (int i = 1; i <= n; i++)
        {
            int square = (int)pow(i, 2);
            printf("%d ", square);
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\nExiting at Parent Process\n");
    }
}