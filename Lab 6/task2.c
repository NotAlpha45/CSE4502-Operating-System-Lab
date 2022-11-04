#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

#define newline printf("\n")

void array_printer(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    newline;
}

int fibonacci_generator(int n, int *fib_terms)
{
    // initialize first and second terms
    int t1 = 0, t2 = 1;
    fib_terms[0] = t1;
    fib_terms[1] = t2;

    // initialize the next term (3rd term)
    int next_term = t1 + t2;
    fib_terms[2] = next_term;

    // print 3rd to nth terms
    for (int i = 3; i < n; ++i)
    {
        t1 = t2;
        t2 = next_term;
        next_term = t1 + t2;
        fib_terms[i] = next_term;
    }
}

int main(int argc, char const *argv[])
{
    int pipe21[2];

    int n;

    printf("Enter fiboncci term to be printed: ");
    scanf("%d", &n);

    int fib_terms[n];

    pid_t pid;

    pid = fork();

    if (pid > 0)
    {

        // Wait for the child to send the data
        wait(NULL);
        printf("Parent Process");
        newline;

        int fib_terms_copy[n];

        // Close the writing end before writing
        close(pipe21[1]);

        // Read from the pipe;
        read(pipe21[0], fib_terms_copy, n * sizeof(int));

        // Close the reading end
        close(pipe21[0]);

        printf("The fibonacci sequence: ");
        array_printer(fib_terms_copy, n);
    }
    else if (pid == 0)
    {
        printf("Child Process");
        newline;

        fibonacci_generator(n, fib_terms);
        array_printer(fib_terms, n);
        newline;

        // Close the reading end before writing
        close(pipe21[0]);

        // Write in the pipe;
        write(pipe21[1], fib_terms, n * sizeof(int));

        // Close the writing end
        close(pipe21[1]);

        exit(0);
    }

    return 0;
}
