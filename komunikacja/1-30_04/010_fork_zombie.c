#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//nowy terminal + ps aux | grep Z

int main() 
{
	int pid = fork();

	if (pid == 0) { 
		//child
       	exit(0);
	}
     
	//parent
   	getchar();
}
