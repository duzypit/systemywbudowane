//http://man7.org/linux/man-pages/man7/unix.7.html#EXAMPLE
#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define PEXIT(str) {perror(str);exit(1);}
#define BUFF_SIZE 256

char * myfifo = "/tmp/myfifo";

int client_init(){
	int client_socket;
	struct sockaddr_un remote;

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

	return client_socket;
	
}

int main(void){
	system("clear");
	int client_socket;

	//char msg[BUFF_SIZE];
	char buffer[BUFF_SIZE] = {0};

	client_socket = client_init();
	
	while(1){
		printf("Give me a command (end == break): ");
		memset(buffer, '\0', BUFF_SIZE);
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer,"\n")] = 0;
		
		if(strcmp(buffer, "end") != 0 && strlen(buffer) > 0){
			if((send(client_socket, buffer, strlen(buffer), 0)) == -1){
				PEXIT("write");
			}
	
		//strcpy(buffer, "END");
		//if((recv(client_socket, buffer, strlen(buffer), 0)) == -1){
		//	PEXIT("read");
		//}
	
		//printf("Result = %s\n", buffer);
		//break;
		} else {
			puts("Bye!");
			close(client_socket);
		}
	}
	return 0;
}
