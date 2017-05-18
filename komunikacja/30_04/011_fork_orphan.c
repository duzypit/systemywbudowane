#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t child_pid = fork();

	if(child_pid == -1)
	{
		printf("error\n");
	}
	else if(child_pid == 0)
	{
		printf("child pid  = %d\n", getpid());
		printf("child ppid = %d\n", getppid());
		sleep(20);
		printf("child pid  = %d\n", getpid());
		printf("child ppid = %d\n", getppid());
	
	}
	else
	{
		printf("parent pid  = %d\n", getpid());
		printf("parent ppid = %d\n", getppid());
		sleep(10);
		printf("parent ends\n");
	}
	
	return 0;
}
