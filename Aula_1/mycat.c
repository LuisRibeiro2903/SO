#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, const char * argv[])
{
    char * line = NULL;
    size_t bufsize;
    while(getline(&line, &bufsize, stdin) > 0)
        printf("%s", line);
    return 0;
}