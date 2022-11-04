// compile with gcc -pthread task1.c -o task1

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define newline printf("\n")

void prime_printer(int n)
{

    bool prime[n + 1];

    memset(prime, true, sizeof(prime));

    for (int p = 2; p * p <= n; p++)
    {
        if (prime[p] == true)
        {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    for (int i = 2; i <= n; i++)
    {
        if (prime[i])
        {
            printf("%d ", i);
        }
    }
    newline;
}

void *user_action(void *dummy_arg)
{
    // Detach the thread from calling thread to ensure it is a
    // seperate thread
    pthread_detach(pthread_self());

    int n;

    printf("Enter number: ");
    scanf("%d", &n);
    prime_printer(n);

    // Exit from current thread
    pthread_exit(NULL);
}

void prime_printer_thread()
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

    printf("Thread ended!");
    newline;

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    prime_printer_thread();
    return 0;
}
