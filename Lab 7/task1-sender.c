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

    while (1)
    {
        int message_id;

        struct message_buffer message;

        // key = ftok("maheen", 48);

        message_id = msgget((key_t)14534, 0666 | IPC_CREAT);

        message.message_type = 1;
        
        int n, i = 1;

        printf("Numbers you want to input: ");
        scanf("%d", &n);

        newline;

        message.message_content[0] = n;

        while (i <= n)
        {
            scanf("%d", &message.message_content[i++]);
        }

        msgsnd(message_id, &message, sizeof(message), 0);

        printf("The data sent is: ");

        array_printer(message.message_content, n + 1);
    }

    return 0;
}
