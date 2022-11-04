#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "myCat.h"
#include "myCopy.h"

int main(int argc, char **argv)
{

    char *commands[] = {"vim",
                        "ls",
                        "cp",
                        "cat",
                        "touch"};

    printf("The available commands:\n");

    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", commands[i]);
    }

    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("-------------\n");
        printf("Child Process\n");
        printf("-------------\n");

        printf("write your command: ");

        char command[10];
        scanf("%s", command);
        printf("%s\n", command);

        if (strcmp(command, "ls") == 0)
        {
            execlp("ls", "ls", "-l", NULL);
        }

        else if (strcmp(command, "vim") == 0)
        {
            char filename[256];
            printf("Enter filename: ");
            scanf("%s", filename);
            execlp("vim", "vim", filename, NULL);
        }

        else if (strcmp(command, "cp") == 0)
        {
            char original_file[256], copy_file[256];

            printf("Enter original file: ");
            scanf("%s", original_file);

            printf("Enter copy file: ");
            scanf("%s", copy_file);

            // execl("./myCopy", "./myCopy", original_file, copy_file, NULL);
            myCopy(original_file, copy_file);
        }

        else if (strcmp(command, "touch") == 0)
        {
            char filename[256];

            printf("Enter filename: ");
            scanf("%s", filename);

            myTouch(filename);
        }
        else if (strcmp(command, "cat") == 0)
        {
            char filename[256];

            printf("Enter filename: ");
            scanf("%s", filename);

            // execl("./myCat", "./myCat", filename, NULL);
            myCat(filename);
        }
        else
        {
            printf("Command not recognized!\n");
        }
    }
    else if (pid > 0)
    {

        wait(NULL);
        main(argc, argv);
    }

    // wait(NULL);
}