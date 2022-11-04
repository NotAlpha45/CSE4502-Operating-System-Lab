#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define newline printf("\n")
#define MAX_MEMORY 1024

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
    for (int i = 1; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{

    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(int) * MAX_MEMORY, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    int *array = (int *)shmat(shmid, (void *)0, 0);

    int n = array[0];

    printf("Data read from memory: ");

    array_printer(array, n + 1);

    int element;

    printf("Enter element to search: ");
    scanf("%d", &element);

    // Again, the first index contains the size, and hence, start from index 1.
    printf("The element is at index = %d", binary_search(array, 1, n, element) - 1);
    newline;

    // detach from shared memory
    shmdt(array);

    // dearrayoy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}