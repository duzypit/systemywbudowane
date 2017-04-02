//http://man7.org/linux/man-pages/man7/unix.7.html#EXAMPLE
#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
int main(void){

	int data_socket, ret;
	struct sockaddr_un name;
	char * myfifo = "/tmp/myfifo";
	char * msg = "dycha";
	char buffer[10];

	data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);	
	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, myfifo, sizeof(name.sun_path)-1);
	
	ret = connect(data_socket, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));
	ret = write(data_socket, msg, strlen(msg)-1);
	strcpy(buffer, "END");
	ret =read(data_socket, buffer, strlen(buffer)+1);
	printf("Result = %s\n", buffer);
	close(data_socket);
	return 0;
}
