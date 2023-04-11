#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#define LINHAS 50
#define COLUNAS 1000

int main(int argc, char * argv[])
{
    n = atoi(argv[1]);

    srand( time (NULL));

    pid_t p;
    int i, j;
    for(i = 0; i < LINHAS; i++)
    {
        p = fork();
        switch(p)
        {
            case -1:
            
            case 0:
                for(j = 0; j < COLUNAS; j++)
                    if (n == a[i][j])
                    {
                        printf("merda");
                        exit(0);
                    }
                exit(1);
        }
    }
}