#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("child pid = %d\n",getpid());
		printf("child parent pid = %d\n", getppid());
	}
	else if(pid > 0)
	{
		printf("parent pid = %d\n",getpid());
		printf("parent parent pid = %d\n",getppid());
	}
	else
	{
		printf("error");
	}
	
	return 0;
}
