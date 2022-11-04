#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void myTouch(char *filename)
{
    int file_handle = open(filename, O_RDONLY);

    if (file_handle > 0)
    {
        printf("File already exists!\n");
    }
    else
    {
        printf("Created New File\n");
        file_handle = open(filename, O_CREAT);
    }
}