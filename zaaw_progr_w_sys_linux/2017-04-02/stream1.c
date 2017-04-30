#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//potoki nienazwane
//man 2 write

int main(void){

	int fd[2], nbytes;
	pid_t childpid;
	char string[] = "Hello world \n";
	char readbuffer[80];
	pipe(fd);
//fork zawiódł
	if((childpid = fork()) == -1){
//man perror
		perror("fork");
		exit(1);
	}
printf("fd[0] : %d\n",fd[0]);
printf("fd[1] : %d\n",fd[1]);
// jeden proces może tylko czytać, drugi tylko pisać! man file descriptor
// sprawdzam czy jestem dzieckiem - dzieci procesu maja childpid == 0. Childpid > 0  - oznacza ze proces ma dziecko 
	if(childpid == 0){
//zamyka deskryptor do odczytu bonie bedzie pisal
		close(fd[0]);
		write(fd[1], string, (strlen(string)+1));
		exit(0);
	} else {
//zamyka fd do zapisu bo nie będzie pisal
		close(fd[1]);
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		if(nbytes == 0){
			perror("read");
			exit(0);
		}
		printf("Recieved string %s", readbuffer);
	}
	return(0);
}
