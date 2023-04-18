#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    int fd = open("/tmp/fifo" , O_RDONLY);
    char buf[1024];
    int r;
    while ((r = read(fd, buf, 1024)) > 0)
    {
        write(STDOUT_FILENO, buf, r);
    }
    close(fd);
    return 0;
}