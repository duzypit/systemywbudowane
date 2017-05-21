#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() 
{
	int status;
	int ret;     
	
	for(int i = 0 ; i < 10 ; i++)
	{
		int pid = fork();

		if(pid == 0)
		{
			printf("child %d\n", getpid());
			sleep(10+i);
			printf("child %d - konczymy prace\n", getpid());
			exit(0);
		}
	}

	for(int i = 0 ; i < 10 ; i++)
	{
		printf("parent - czekamy na zakonczenie child\n");
		ret = wait(&status);			
		printf("parent - po wait ret = %d | status = %d\n", ret, status);
	}

	printf("parent - w koncu koniec\n");
}
