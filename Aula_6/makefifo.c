#include <sys/types.h>
#include <sys/stat.h>

int main ()
{
    mkfifo("/tmp/fifo", 0600);
    return 0;
}