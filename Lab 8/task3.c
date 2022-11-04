// compile with gcc -pthread task3.c -o task3

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define newline printf("\n")

// Declared globally to make available to all threads
int result_matrix[1000][1000], matrix_a[1000][1000], matrix_b[1000][1000];
int row_a, row_b, col_a, col_b, row_indx = 0, col_indx = 0;

// Generates the [i, j] th element
int matrix_element_generator(int i, int j)
{
    int result = 0;
    for (int k = 0; k < row_b; k++)
    {
        result += (matrix_a[i][k] * matrix_b[k][j]);
    }

    return result;
}

void *user_action(void *dummy_arg)
{
    // Detach the thread from calling thread to ensure it is a
    // seperate thread
    pthread_detach(pthread_self());

    result_matrix[row_indx][col_indx] = matrix_element_generator(row_indx, col_indx);

    // Exit from current thread
    printf("Seperate Thread ended!");
    newline;

    pthread_exit(NULL);
}

void fibonacci_printer_thread()
{
    while (true)
    {
        printf("Enter rows of A: ");
        scanf("%d", &row_a);
        printf("Enter columns of A: ");
        scanf("%d", &col_a);

        printf("Enter rows of B: ");
        scanf("%d", &row_b);
        printf("Enter columns of B: ");
        scanf("%d", &col_b);

        if (row_b != col_a)
        {
            printf("Rows of B are not equal to cols of A");
            newline;
            continue;
        }
        else
        {
            break;
        }
    }

    newline;
    printf("For matrix A: ");
    newline;
    for (int i = 0; i < row_a; i++)
    {
        for (int j = 0; j < col_a; j++)
        {
            printf("Enter A(%d, %d): ", i, j);
            scanf("%d", &matrix_a[i][j]);
        }
    }

    newline;
    printf("For matrix B: ");
    newline;
    for (int i = 0; i < row_b; i++)
    {
        for (int j = 0; j < col_b; j++)
        {
            printf("Enter B(%d, %d): ", i, j);
            scanf("%d", &matrix_b[i][j]);
        }
    }

    pthread_t thread_id;
    int thread_number = 0;

    // Creating new threads for calculation of each matrix element. The new matrix
    // is (row_a x col_b)
    newline;
    for (row_indx = 0; row_indx < row_a; row_indx++)
    {
        /* code */
        for (col_indx = 0; col_indx < col_b; col_indx++)
        {
            pthread_create(&thread_id, NULL, user_action, NULL);

            printf("Thread %d created", thread_number);
            thread_number++;
            newline;

            // The threads must wait for one another as they are sharing
            // row_indx and col_indx that may be modified undesirebly as
            // threads are independent from one another.
            pthread_join(thread_id, NULL);
        }
    }

    newline;
    printf("Matrix Result:");
    newline;
    for (int i = 0; i < row_a; ++i)
    {
        for (int j = 0; j < col_b; ++j)
        {
            printf("%d ", result_matrix[i][j]);
        }
        newline;
    }

    newline;

    printf("Caller Thread ended!");
    newline;

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    fibonacci_printer_thread();
    return 0;
}
