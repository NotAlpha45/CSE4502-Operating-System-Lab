// compile with gcc -pthread task2.c -o task2

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define newline printf("\n")

// Declared globally to make available to all threads
int fib_terms[100000], n;

int fibonacci_generator(int n)
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

void array_printer(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void *user_action(void *dummy_arg)
{
    // Detach the thread from calling thread to ensure it is a
    // seperate thread
    pthread_detach(pthread_self());

    printf("Enter fibonacci terms to generate: ");
    scanf("%d", &n);
    fibonacci_generator(n);

    printf("Fibonacci generated in seperate thread: ");
    array_printer(fib_terms, n);

    // Exit from current thread
    printf("Seperate Thread ended!");
    newline;

    pthread_exit(NULL);
}

void fibonacci_printer_thread()
{

    pthread_t thread_id;

    // Creating a new thread
    pthread_create(&thread_id, NULL, user_action, NULL);

    // Compare the two threads created
    if (pthread_equal(thread_id, pthread_self()))
        printf("Threads are equal\n");
    else
        printf("Threads are not equal\n");

    // Waiting for the created thread to terminate
    pthread_join(thread_id, NULL);

    printf("Generated fibonacci in caller thread: ");
    array_printer(fib_terms, n);

    printf("Caller Thread ended!");
    newline;

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    fibonacci_printer_thread();
    return 0;
}
