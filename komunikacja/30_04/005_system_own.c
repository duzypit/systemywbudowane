#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
 
int main()
{
	printf("moj_prog = %d, uruchamiamy inny program\n", getpid());
	system("./hello");
	printf("moj_prog = %d, konczymy prace\n", getpid());

	return 0;
}
