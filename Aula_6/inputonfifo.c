#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("/tmp/fifo", O_WRONLY);
    if (fd < 0)
    {
        perror("Não funcionou artista");
        exit(-1);
    }
    
    char * buf = malloc(1024);
    int r;
    size_t size;
    while((r = getline(&buf, &size, stdin)) > 0)
    {
        write(fd, buf, r);
    }
    free(buf);
    close(fd);
    return 0;
}