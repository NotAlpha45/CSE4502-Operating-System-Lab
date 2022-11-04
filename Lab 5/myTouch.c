#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    int file_handle = open(argv[1], O_RDONLY);
    printf("%d\n", file_handle);

    if (file_handle > 0)
    {
        printf("File already exists!\n");
    }
    else
    {
        printf("Created New File\n");
        file_handle = open(argv[1], O_CREAT);
    }
}