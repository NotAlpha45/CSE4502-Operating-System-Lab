#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define newline printf("\n")

void array_printer(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

struct message_buffer
{
    long message_type;
    int message_content[1000];
};

int main(int argc, char const *argv[])
{
    // key_t key;
    int message_id;

    struct message_buffer message;

    // key = ftok("maheen", 48);

    long int msg_to_rec = 0;

    message_id = msgget((key_t)14534, 0666 | IPC_CREAT);

    msgrcv(message_id, &message, sizeof(message), msg_to_rec, 0);

    int n = message.message_content[0];

    printf("The %d data received is: ", n);

    array_printer(message.message_content, n + 1);

    msgctl(message_id, IPC_RMID, NULL);

    return 0;
}
