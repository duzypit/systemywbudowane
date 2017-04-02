#include <stdio.h>
//#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include <stdlib.h>

//kolejki nazwane
// mknod, mkfifo - można utworzyc kolejki z basha
int main(void){

	int fd;
	char * myfifo = "/tmp/myfifo";

	mkfifo(myfifo, 0666);
	fd = open(myfifo, O_WRONLY);
	write(fd, "hi", sizeof("hi"));
	close(fd);
	unlink(myfifo);

	return 0;

}
