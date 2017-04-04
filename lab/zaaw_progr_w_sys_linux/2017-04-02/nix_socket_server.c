#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 1024
//kolejki nazwane
// mknod, mkfifo - można utworzyc kolejki z basha
int main(void){

	int connection_socket, data_socket, result, len;
	struct sockaddr_un local, remote;

	char * buffer = calloc(BUFF_SIZE, sizeof(char));
	char * myfifo = "/tmp/myfifo";
	//socket(domain, type, protocol) - jeśli protocol == 0, socket wybierze sam na podstawie parametru type
	connection_socket = socket(AF_UNIX, SOCK_STREAM,0);
	if (connection_socket == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}



	local.sun_family = AF_UNIX;
	//kopiuje określoną ilość znaków z łańcucha źródłowego do docelowego strncpy(dest, src, size)
	strncpy(local.sun_path, myfifo, sizeof(local.sun_path)-1);


	
	//przypisujemy  socket do socket local
	//bind(int socketfd, struct sockaddr * my_addr, int addrlen)
	result = bind(connection_socket, (const struct sockaddr *) &local, sizeof(struct sockaddr_un));
	if (result == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	//listen(int sockfd, int backlog) - backlog jak duża może być kolejka oczekujących połączeń
	result = listen(connection_socket, 20);
	if(result == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	for(;;){
		//accep zwraca socket, poprzedni cały czas słucha czy nie ma połączeń!
		len = sizeof(struct sockaddr_un);

		//accept - remote będzie wypełniona struct sockaddr_un z klienta, len wiadomka
		data_socket = accept(connection_socket, &remote, &len);

		for(;;){
			//read(int socketfd, void *buf, size_t nbytes) - args: deskryptor, char array na content, ilość bajtów do przeczytania
			result = read(data_socket, buffer, BUFF_SIZE);
			if(result == -1){
				perror("read");
				exit(EXUT_FAILURE);
			}
			break;
		}
		break;
	}

	printf("%s \n", buffer);
	close(data_socket);
	close(connection_socket);

	return 0;

}
