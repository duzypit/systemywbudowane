//http://man7.org/linux/man-pages/man7/unix.7.html#EXAMPLE
#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define PEXIT(str) {perror(str);exit(1);}
#define BUFF_SIZE 1024
int main(void){
	system("clear");
	int client_socket;
	struct sockaddr_un remote;
	char * myfifo = "/tmp/myfifo";
	char * msg = "dycha";
	char buffer[10];
	//0 na końcu oznacza, wybierz protokół na podstawie przedostatniego parametru 
	if((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		PEXIT("socket");
	}

	puts("Tryin' to connect...");

	remote.sun_family = AF_UNIX;
	strncpy(remote.sun_path, myfifo, sizeof(remote.sun_path)-1);


	if(connect(client_socket, (const struct sockaddr *) &remote, sizeof(struct sockaddr_un)) == -1){
		PEXIT("connect");
	}

	puts("Connected.");

	if((send(client_socket, msg, strlen(msg), 0)) == -1){
		PEXIT("write");
	}

	strcpy(buffer, "END");
	if((recv(client_socket, buffer, strlen(buffer), 0)) == -1){
		PEXIT("read");
	}

	printf("Result = %s\n", buffer);
	close(client_socket);
	return 0;
}
