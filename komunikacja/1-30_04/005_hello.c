#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
 
int main()
{
	printf("hello z innego programu pid = %d\n", getpid());

	return 0;
}
