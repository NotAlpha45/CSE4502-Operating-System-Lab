#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "myTouch.h"

void myCat(char *filename)
{
    // Getting the size of the file to be read;
    struct stat st;
    stat(filename, &st);
    int file_size = st.st_size;

    char *buffer = calloc(file_size * sizeof(char), sizeof(char));

    int file_handle = open(filename, O_RDONLY);

    if (file_handle > 0)
    {
        if (file_size == 0)
        {
            printf("File is empty!\n");
        }
        else
        {
            int file_stat = read(file_handle, buffer, file_size);
            buffer[file_size] = '\0';
            printf("%s\n", buffer);
        }
    }
    else
    {
        printf("Created new file %s!\n", filename);
        myTouch(filename);
        myCat(filename);
    }
}