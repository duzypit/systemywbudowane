#include <unistd.h> // getpid(), getppid()
#include <sys/types.h> 
#include <stdio.h>

int main()
{
	printf("pid = %d\n", getpid());
	printf("ppid = %d\n", getppid());

	return 0;
}
