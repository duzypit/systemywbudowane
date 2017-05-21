#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main()
{
	pid_t pid, sid;

	//stworz proces potomny
	pid = fork();
	if(pid < 0)
		exit(EXIT_FAILURE);

	//zakoncz proces rodzica
	if(pid > 0)
		exit(EXIT_SUCCESS);

	//zmien prawa do plikow
	umask(0);

	//nadaj nowe sid (set sesion id)
	sid = setsid();
	if(sid < 0)
		exit(EXIT_FAILURE);

	//zmien biezacy katalog na /
	if((chdir(("/")) < 0))
		exit(EXIT_FAILURE);

	//zamknij stdin, stdout, stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	//kod deamona
	while(1)
	{
		sleep(10);
	}

	return 0;
}
