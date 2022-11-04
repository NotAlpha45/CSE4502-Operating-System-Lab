#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    execlp("gcc", "gcc", "myCopy.c", "-Wno-implicit", "-o", "myCopy", NULL);
    execlp("gcc", "gcc", "myTouch.c", "-o", "myTouch", NULL);
    execlp("gcc", "gcc", "myCat.c", "-Wno-implicit", "-o", "myCat", NULL);
}