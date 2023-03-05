#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

/**
 * @brief My version of function 'cp'
 * 
 * @param src source path   
 * @param dest destination path
 * @return int control integer
 */
int mycopy (const char * src, const char * dest)
{
    int fd_src = open(src, O_RDONLY);
    int fd_dest = open(dest, O_CREAT | O_TRUNC | O_WRONLY, 0660);
    int size = lseek (fd_src, 0, SEEK_END);
    lseek(fd_src, 0, SEEK_SET);
    char buf [size];
    if (read (fd_src, buf, size)<= 0 || write (fd_dest, buf, size)<= 0)
        return -1;
    close(fd_src);
    close(fd_dest);
    return 0;
}




int main(int argc, const char * argv[])
{
    if (argc == 3)
        return mycopy (argv[1], argv[2]);
    return -1;
}