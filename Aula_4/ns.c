#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main ()
{
    execlp("ls", "ls", "-l", NULL);
    perror("Não funcionou campeão");    
}