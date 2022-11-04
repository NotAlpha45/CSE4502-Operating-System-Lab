#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>
#define MAX_MEMORY 1024
#define newline printf("\n")

int fibonacci_generator(int n, int *fib_terms)
{
    // initialize first and second terms. Note that since the first element
    // of the array will contain the number of elements, we will start from 1.
    int t1 = 0, t2 = 1;
    fib_terms[1] = t1;
    fib_terms[2] = t2;

    // initialize the next term (3rd term)
    int next_term = t1 + t2;
    fib_terms[3] = next_term;

    // print 4th to nth terms
    for (int i = 4; i < n; ++i)
    {
        t1 = t2;
        t2 = next_term;
        next_term = t1 + t2;
        fib_terms[i] = next_term;
    }
}

// In our array, the fist element will be the length of the array, so start from 1.
void array_printer(int *array, int n)
{
    for (int i = 1; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child Process");
        newline;

        // ftok to generate unique key
        key_t key = ftok("shmfile", 65);

        int n, i = 1;

        printf("Fibonacci numbers to get: ");
        scanf("%d", &n);

        // shmget returns an identifier in shmid
        int shmid = shmget(key, sizeof(int) * MAX_MEMORY, 0666 | IPC_CREAT);

        // shmat to attach to shared memory
        int *array = (int *)shmat(shmid, (void *)0, 0);

        array[0] = n;

        fibonacci_generator(n + 1, array);

        printf("Data written in memory: ");
        array_printer(array, n + 1);

        // detach from shared memory
        shmdt(array);

        newline;
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("Parent Process");
        newline;

        // ftok to generate unique key
        key_t key = ftok("shmfile", 65);

        // shmget returns an identifier in shmid
        int shmid = shmget(key, sizeof(int) * MAX_MEMORY, 0666 | IPC_CREAT);

        // shmat to attach to shared memory
        int *array = (int *)shmat(shmid, (void *)0, 0);

        int n = array[0];

        printf("Data read from memory: ");

        array_printer(array, n + 1);

        // detach from shared memory
        shmdt(array);

        // destroy the shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
