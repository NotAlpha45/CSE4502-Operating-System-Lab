// including Header Files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

// Bubble Sort Functions
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

// Binary Search Function
int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

int main()
{

    int fd1[2]; // Used to store two ends of first pipe
    int fd2[2]; // Used to store two ends of second pipe
    int fd3[2]; // Used to store two ends of third pipe

    pid_t p;

    if (pipe(fd1) == -1) // for sending array to child from parent
    {
        printf("Pipe Failed");
        return 1;
    }
    if (pipe(fd2) == -1) // for sending array to parent from child
    {
        printf("Pipe Failed");
        return 1;
    }
    if (pipe(fd3) == -1)
    {
        printf("Pipe Failed");
        return 1;
    }

    p = fork();

    if (p < 0)
    {
        printf("fork Failed");
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        int size;
        printf("Enter the number of elrments in Array:");
        scanf("%d", &size);

        int i, output_int[size], fixed_int[size];
        printf("Enter your elements:\n");
        for (i = 0; i < size; i++)
        {
            scanf("%d", &fixed_int[i]);
        }

        int searchNumber;
        printf("Enter element you wanna search:");
        scanf("%d", &searchNumber);

        // Close reading end of first pipe
        close(fd1[0]);

        // Write and close writing end of first pipe.
        write(fd1[1], fixed_int, size * sizeof(int));
        close(fd1[1]);

        // Write and close writing end of third pipe.
        write(fd3[1], &size, sizeof(int));
        close(fd3[1]);

        printf("Data written in pipe: \n");
        for (i = 0; i < size; i++)
        {
            printf("%d ", fixed_int[i]);
        }
        printf("\n");

        // Wait for child to send a string
        wait(NULL);
        // Read using second pipe
        read(fd2[0], output_int, 100);

        printf("Data read from pipe in parent: \n");
        for (i = 0; i < size; i++)
        {
            printf("%d ", output_int[i]);
        }
        printf("\n");

        printf("Searching for %d ... \n", searchNumber);
        int result = binarySearch(output_int, 0, size - 1, searchNumber);
        (result == -1)
            ? printf("Element is not present in array")
            : printf("Element is present at index %d", result);
        printf("\n");

        close(fd2[0]);
    }

    // child process
    else
    {
        // Close writing end of third pipe
        close(fd3[1]);
        // Read using third pipe
        int size;
        read(fd3[0], &size, sizeof(int));

        close(fd1[1]); // Close writing end of first pipe
        // Read using first pipe
        int outp_int[size], i;
        read(fd1[0], outp_int, 100);

        printf("Data read from pipe in child: \n");
        for (i = 0; i < size; i++)
        {
            printf("%d ", outp_int[i]);
            // if(outp_int[i]%2==1)
            //     outp_int[i]+=5;
            // else if(outp_int[i]%2==0)
            //     outp_int[i]+=10;
        }
        printf("\n");

        // sorting-bubbleSort
        bubbleSort(outp_int, size);
        printf("Sorted Data in child: \n");
        for (i = 0; i < size; i++)
        {
            printf("%d ", outp_int[i]);
            // if(outp_int[i]%2==1)
            //     outp_int[i]+=5;
            // else if(outp_int[i]%2==0)
            //     outp_int[i]+=10;
        }
        printf("\n");

        close(fd1[0]);

        close(fd2[0]);

        // Write and close writing end of second pipe. Goes back to Parent
        write(fd2[1], outp_int, size * sizeof(int));

        close(fd2[1]);

        exit(0);
    }
}