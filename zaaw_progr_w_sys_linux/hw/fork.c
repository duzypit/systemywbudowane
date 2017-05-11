#include <stdio.h>
#include <unistd.h> //getpid
#include <sys/types.h> // //getpid, waitpid
#include <sys/wait.h>	//waitpid

int main (void){
	int status;
	pid_t cpid = fork();

	if(cpid == 0){
		while(1){
			pid_t ppid = getppid(); 
		}
	}
	waitpid(cpid, &status, WEXITED);
	puts("parent bye");

	return 0;
}