#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define MAX_MEMORY 1024
#define newline printf("\n")

void array_printer(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// We are storing the array size in the first index, hence, the bubble sort starts at 1
void bubble_sort(int *array, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (array[i] < array[j])
            {
                swap(&array[i], &array[j]);
            }
        }
    }
}

int main()
{

    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    int n, i = 1;

    printf("Numbers you want to input: ");
    scanf("%d", &n);
    newline;

    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(int) * MAX_MEMORY, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    int *array = (int *)shmat(shmid, (void *)0, 0);

    array[0] = n;

    while (i <= n)
    {
        scanf("%d", &array[i++]);
    }

    bubble_sort(array, n + 1);

    printf("Data written in memory: ");
    array_printer(array, n + 1);

    // detach from shared memory
    shmdt(array);

    return 0;
}