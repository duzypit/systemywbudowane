#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() 
{
	int pid = fork();
	int status, ret;

	if(pid == -1)
	{
		printf("error\n");
	}
	else if(pid == 0)
	{
		printf("child %d\n", getpid());
		sleep(10);
		printf("child %d | konczymy prace\n", getpid());
		exit(0);
	}
	else
	{
		printf("parent %d | czekamy na zakonczenie child\n", getpid());
		ret = wait(&status);
		printf("parent %d |  po wait ret = %d | status = %d\n", getpid(), ret, status);
	}
}
