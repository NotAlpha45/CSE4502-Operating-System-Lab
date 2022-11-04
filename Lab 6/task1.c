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

int binary_search(int *arr, int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binary_search(arr, l, mid - 1, x);

        return binary_search(arr, mid + 1, r, x);
    }
    return -1;
}

void array_printer(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int n;
    printf("Enter how many numbers to input: ");
    scanf("%d", &n);
    int array[n];
    int i = 0;

    printf("Input numbers: \n");
    while (i < n)
    {
        int inp;
        scanf("%d", &array[i++]);
    }

    // pipe12: parent => child, pipe21: child => parent
    int pipe12[2], pipe21[2];
    pid_t pid;

    // Make the pipes
    pipe(pipe12);
    pipe(pipe21);

    pid = fork();

    if (pid > 0)
    {

        // Wait for the child to send the data
        wait(NULL);

        printf("Parent Process\n");

        int sorted_array[n];

        // Close writing end before reading
        close(pipe21[1]);
        // Read from child and close reading end
        read(pipe21[0], sorted_array, n * sizeof(int));
        close(pipe21[0]);

        printf("The sorted array: ");

        array_printer(sorted_array, n);

        int value;

        printf("Enter value to be searched: \n");
        scanf("%d", &value);

        printf("The value is in index: %d\n", binary_search(sorted_array, 0, n - 1, value));
    }
    else if (pid == 0)
    {

        printf("Child Process\n");

        bubble_sort(array, n);
        printf("Sorted array: ");
        array_printer(array, n);

        // Close reading end before writing
        close(pipe21[0]);

        // Writing in the pipe
        write(pipe21[1], array, n * sizeof(int));

        // Close writing end of the pipe after writing
        close(pipe21[1]);

        exit(0);
    }
}