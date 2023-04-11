#include <unistd.h>     /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>   /* chamadas wait*() e macros relacionadas */
#include <sys/sysinfo.h>
#include <fcntl.h>      /* responsável pelas macros das funções open, read, ... */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct found
{
    int linha;
    int coluna;
}Found;

int ex1 (int N)
{
    int p[2];
    pipe (p);
    if (!fork())
    {
        close (p[1]);
        int n;
        read (p[0], &n, sizeof (int));
        close (p[0]);
        printf ("%i\n", n);
        _exit (0);
    }
    write (p[1], &N, sizeof (int));
    close (p[1]);
    wait (NULL);
    return 0;
}

int ex2 (int N)
{
    int p[2];
    pipe (p);
    if (!fork())
    {
        close (p[1]);
        int n;
        read (p[0], &n, sizeof (int));
        close (p[0]);
        printf ("%i\n", n);
        _exit (0);
    }
    sleep(5);
    write (p[1], &N, sizeof (int));
    close (p[1]);
    wait (NULL);
    return 0;
}

int ex3 (int N)
{
    int p[2];
    pipe (p);
    if (!fork())
    {
        close (p[0]);
        write (p[1], &N, sizeof (int));
        close (p[1]);
        _exit (0);
    }
    close (p[1]);
    int n;
    read (p[0], &n, sizeof (int));
    close (p[0]);
    printf ("%i\n", n);
    wait (NULL);
    return 0;
}

int ex4 (int N)
{
    int p[2];
    pipe (p);
    if (!fork())
    {
        close (p[0]);
        write (p[1], &N, sizeof (int));
        write (p[1], &N, sizeof (int));
        close (p[1]);
        _exit (0);
    }
    close (p[1]);
    int n;
    sleep (2);
    read (p[0], &n, sizeof (int));
    read (p[0], &n, sizeof (int));    
    close (p[0]);
    printf ("%i\n", n);
    wait (NULL);
    return 0;
}

int ex5 (int N)
{
    int p[2];
    pipe (p);
    if (!fork())
    {
        close (p[0]);
        for (int i= 0; i< N; i++)
        {
            write (p[1], &i, sizeof (int));
        }
        close (p[1]);
        _exit (0);
    }
    int n;
    close (p[1]);
    while (read (p[0], &n, sizeof (int))> 0)
    {
        printf ("%i\n", n);
    }
    close (p[0]);
    wait (NULL);
    return 0;
}

int ex6 (int * a, int n, int LINHAS, int COLUNAS, Found * vetor)
{
    int pip[2];
    pipe(pip);
    pid_t p;
    int i,j;
    Found f, reader;
    for (i = 0; i < LINHAS; i++)
    {
        f.linha = i;
        p = fork();
        switch(p) 
        {
            case -1:
                perror ("Erro no fork!");
                _exit(-1);
            case 0:
                close(pip[0]);
                for(j = 0; j < COLUNAS; j++)
                    if (n == a[i * COLUNAS + j] )
                    {
                        f.coluna = j;
                        write (pip[1], &f, sizeof (Found));
                    }
                close(pip[1]);
                _exit(0);
            case 1:
                continue;
        }
    }
    i = 0;
    close(pip[1]);
    while (read (pip[0], &reader, sizeof(Found)) > 0)
    {
        vetor[i].linha = reader.linha;
        vetor[i].coluna = reader.coluna;
        printf("ENCONTRADO EM LINHA %d, COLUNA %d\n", vetor[i].linha, vetor[i].coluna);
        i++;
    }
    close(pip[0]);

}

int main (int argc, char* argv[])
{
    int matriz [10][10000];
    int i, j, ret;
    if (argc>= 2)
    {
        int n= atoi (argv[1]);
        switch (n)
        {
            case 1:
                return ex1 (atoi (argv[2]));
            case 2:
                return ex2 (atoi (argv[2]));
            case 3:
                return ex3 (atoi (argv[2]));
            case 4:
                return ex4 (atoi (argv[2]));
            case 5:
                return ex5 (atoi (argv[2]));
            case 6:
                srand(time(NULL));
                for(i = 0; i < 10; i++)
                    for(j = 0; j < 10000; j++)
                        matriz[i][j] = rand()%1000;
                Found * vetor = malloc(100000 * sizeof(Found));
                ret = ex6(*matriz, 450, 10, 10000, vetor);
                return ret;

      }
    }
    return -1;
}