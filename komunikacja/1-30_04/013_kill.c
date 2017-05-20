#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

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
		sleep(20);
	}
	else
	{
		printf("parent pid  = %d\n", getpid());
		if(!kill(child_pid, SIGKILL))
			printf("child killed ok\n");	
		else
			printf("child error\n");		
	}
	
	return 0;
}
