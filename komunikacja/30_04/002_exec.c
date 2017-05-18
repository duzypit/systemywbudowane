#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
 
int main()
{
	printf("moj_prog = %d, uruchamiamy inny program\n", getpid());
	
	//no PATH, full path needed
	execl("/bin/ps", "ps", "-u", NULL);

	//from PATH
	//execlp("ps", "ps", "-u", NULL);
	
	//wlasne srodowsiko
	//char* env[] = {"HOME=/tmp", NULL};
	//execle("/bin/ps", "ps", "-u", NULL, env);

	
	//to samo co execl + argumenty przekazane w tablicy
	//char* arguments[] = {"ps", "-u", NULL};
	//execv("/bin/ps", arguments);

	//to samo co execlp ale argumenty przekazane w tablicy
	//char* arguments2[] = {"ps", "-u", NULL};
	//execvp("ps", arguments2);

	//to samo co execle + argumenty przekazane w tablicy
	//char* ps_argv3[] ={"ps", "-u", NULL};
	//char* ps_envp3[] = {"HOME=/tmp", NULL};
	//execve("/bin/ps", ps_argv3, ps_envp3);
	
	printf("moj_prog = %d, konczymy prace\n", getpid());

	return 0;
}
