#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define newline printf("\n")

const int no_of_process = 3;

int process_worker(int id, int parent_id, char *task_name, int file_name_size, int pipe_end)
{
    printf("I am process: %d, I am doing %s\n", id, task_name);
    printf("My parent is %d\n", parent_id);
    newline;

    char filename[file_name_size];
    read(pipe_end, filename, file_name_size);
    close(pipe_end);

    // A file pointer to be used in writing
    FILE *fh;

    fh = fopen(filename, "w");

    fprintf(fh, "%s", task_name);

    fclose(fh);

    // Exit after doing the process
    exit(0);
}

int main()
{

    pid_t pid_array[no_of_process];
    int pipe_array[no_of_process][2];

    char *tasks[10] = {"palindrome_checking", "password_strength_checking", "prime_number_generation"};
    char *filenames[10] = {"task1.txt", "task2.txt", "task3.txt", "task4.txt"};

    printf("Start of parent process, %d\n", getpid());
    newline;

    for (int i = 0; i < no_of_process; i++)
    {
        char *file = filenames[i];
        char *task = tasks[i];

        pipe(pipe_array[i]);
        write(pipe_array[i][1], file, strlen(file) + 1);
        close(pipe_array[i][1]);

        pid_t current_process = fork();

        if (current_process == 0)
        {
            pid_array[i] = current_process;
            process_worker(getpid(), getppid(), task, strlen(file) + 1, pipe_array[i][0]);
        }
    }

    // Wait for all the child process to complete
    for (int i = 0; i < no_of_process; i++)
    {
        wait((pid_array + i));
    }

    newline;
    printf("End of parent process\n");

    return 0;
}