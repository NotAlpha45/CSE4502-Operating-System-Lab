#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    // Getting the size of the file to be read;
    struct stat st;
    stat(argv[1], &st);
    int file_size = st.st_size;

    char *buffer = calloc(file_size * sizeof(char), sizeof(char));

    int file_handle = open(argv[1], O_RDONLY);

    if (file_handle > 0)
    {
        int file_stat = read(file_handle, buffer, file_size);
        buffer[file_size] = '\0';
        printf("%s\n", buffer);
    }
    else
    {
        printf("Could not read!\n");
    }
}