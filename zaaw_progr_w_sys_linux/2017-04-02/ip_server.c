#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PEXIT(str) {perror(str);exit(1);}
#define BUFF_SIZE 256
char * myfifo = "/tmp/myfifo";	

int server_init(){
	int connection_socket, result;
	struct sockaddr_un local;
	
	//socket(domain, type, protocol) - jeśli protocol == 0, socket wybierze sam na podstawie parametru type
	connection_socket = socket(AF_UNIX, SOCK_STREAM,0);
	if (connection_socket == -1){
		PEXIT("socket");
	}	

	local.sun_family = AF_UNIX;
	//kopiuje określoną ilość znaków z łańcucha źródłowego do docelowego strncpy(dest, src, size)
	strncpy(local.sun_path, myfifo, sizeof(local.sun_path)-1);

	//przypisujemy  socket do socket local
	//bind(int socketfd, struct sockaddr * my_addr, int addrlen)
	result = bind(connection_socket, (const struct sockaddr *) &local, sizeof(struct sockaddr_un));
	if (result == -1){
		PEXIT("bind");
	}	

	//listen(int sockfd, int backlog) - backlog jak duża może być kolejka oczekujących połączeń
	result = listen(connection_socket, 20);
	if(result == -1){
		PEXIT("listen");
	}
	puts("Up & runnin'");
	return connection_socket;
}

s_parse(char *buff_ptr){
	if (strcmp(*buff_ptr, "list") != 0){
		
	}
	
}

int main(void){
	system("clear");

	int data_socket, connection_socket, len, result;
	struct sockaddr remote;
	char buffer[BUFF_SIZE] = {0};
	char *buff_ptr = &buffer;

	connection_socket = server_init();

	while(strcmp(*buff_ptr, "end") != 0){
		
		//accep zwraca socket, poprzedni cały czas słucha czy nie ma połączeń!
		len = sizeof(struct sockaddr);

		//accept - remote będzie wypełniona struct sockaddr_un z klienta, len wiadomka
		if((data_socket = accept(connection_socket, &remote, &len)) == -1){
			PEXIT("accept");
		}

		puts("Connected...");

		while(strcmp(*buff_ptr, "end") != 0){
			memset(*buff_ptr, '\0', BUFF_SIZE);
			//read(int socketfd, void *buf, size_t nbytes) - args: deskryptor, char array na content, ilość bajtów do przeczytania
			result = recv(data_socket, *buff_ptr, BUFF_SIZE, 0);
			if(result == -1){
				PEXIT("read");
			}
			
			s_parse(*buff_ptr);
			
			//printf("%s \n", buffer);
			sleep(1);			
			buffer[strcspn(buffer,"\n")] = 0;
			if(strcmp(buffer, "end") == 0){
				puts("End detected...");
				//break;

			}
		}
		
		//break;
	}

	
	close(data_socket);
	close(connection_socket);
	unlink(myfifo);

	return 0;

}
