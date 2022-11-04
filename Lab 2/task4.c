/*
Currently, any variable shared in a process, will have it's copies passed in the processes.
Therefore, it is not possible for a variable to be modified in one process and another process
use that modification. Therefore, an array sorted in the child process will not be sorted in the parent process. 
*/

#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

#define newline printf("\n")

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[i] < array[j])
            {
                swap(&array[i], &array[j]);
            }
        }
    }
}

void array_printer(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {1, 4, 2, 3}, n = 4;

    printf("Original array: ");
    array_printer(arr, n);
    newline;

    pid_t pid;
    pid = fork();

    if (pid > 0)
    {
        /*The array is not sorted in the parent process, despite being
        sorted in the child process*/
        printf("Parent process\n");
        array_printer(arr, n);
        newline;
    }
    else if (pid == 0)
    {
        printf("Child Process\n");
        bubble_sort(arr, n);
        array_printer(arr, n);
        newline;
    }

    return 0;
}
