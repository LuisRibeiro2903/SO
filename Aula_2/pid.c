#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, const char * argv[])
{
    /* pid_t pid = getpid();  // pid do processo atual
    pid_t ppid = getppid();  // pid do pai do processo atual
    printf("pid : %d; ppid: %d\n", pid, ppid); */

    if(argc == 1)
    {
        pid_t pid, terminated;
        int i, status;
        for(i = 0; i < 10; i++)
        {
            if((pid = fork()) == 0)
            {
                //filho 
                printf("[filho %d] pid = %d\n", i + 1, getpid());
                printf("[filho %d] ppid = %d\n", i + 1, getppid());
                _exit(i+1);
            }
            else
            {
                //pai
                terminated = wait(&status);
                printf("[pai] Código de saída: %d\n", WEXITSTATUS(status));
            }

        }
    }
    else
    {
        pid_t pid, terminated;
        int i, status;
        for(i = 0; i < 10; i++)
        {
            if(!(pid = fork()))
            {
                //filho
                printf("[filho %d] pid = %d\n", i + 1, getpid());
                printf("[filho %d] ppid = %d\n", i + 1, getppid());
                _exit(i+1);
            }
        }
        for(i = 0; i < 10; i++)
        {
            terminated = wait(&status);
            printf("[pai] Código de saída: %d do processo %d\n", WEXITSTATUS(status), terminated);
        }
    }



    /* if((pid = fork()) == 0)
    {
        //filho
        printf("[filho %d] pid = %d\n", i, getpid());
        printf("[filho] ppid = %d\n", getppid());
        _exit(i);
    }
    else
    {
        //pai
        printf("[pai] pid = %d\n", getpid());
        printf("[pai] ppid = %d\n", getppid());
        printf("[pai] pid filho = %d\n", pid);
        i--;
        printf("[pai] i = %d\n", i);

        int status;
        pid_t terminated = wait (&status);
        if (WIFEXITED(status))
            printf("[pai] filho %d terminated\n", terminated);
        else
            printf("error");
    } */
    return 0;
}