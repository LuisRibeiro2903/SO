#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, const char * argv[])
{
	printf("Meu PID = %d, Pai PID = %d\n", getpid(), getppid());
	return 0;
}
