#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PEXIT(str) {perror(str);exit(1);}
#define BUFF_SIZE 256
char * myfifo = "/tmp/myfifo";	

int server_init(){

	return connection_socket;
}

s_parse(char *buff_ptr){
	if (strcmp(*buff_ptr, "list") != 0){
		
	}
	
}

int main(void){
	system("clear");
	
	struct sockaddr_in sa;
	if(inet_pton(AF_INET, "192.168.0.100", &(sa.sin_addr)) <= 0){
		PEXIT("inet_pton");
	}
	
	char buffer[BUFF_SIZE] = {0};
	char *buff_ptr = &buffer;
	//http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
/*	
	struct addrinfo {
		int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
		int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
		int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
		int              ai_protocol;  // use 0 for "any"
		size_t           ai_addrlen;   // size of ai_addr in bytes
		struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
		char            *ai_canonname; // full canonical hostname
	
		struct addrinfo *ai_next;      // linked list, next node
	};

	// (IPv4 only--see struct sockaddr_in6 for IPv6)

	struct sockaddr_in {
		short int          sin_family;  // Address family, AF_INET
		unsigned short int sin_port;    // Port number
		struct in_addr     sin_addr;    // Internet address
		unsigned char      sin_zero[8]; // Same size as struct sockaddr
	};

	//res - ptr to linked list of results
	int getaddrinfo(const char *node,     // e.g. "www.example.com" or IP hostname to connect to
					const char *service,  // e.g. "http" or port number
					const struct addrinfo *hints,
					struct addrinfo **res);	
	*/


	while(strcmp(*buff_ptr, "end") != 0){
		

		len = sizeof(struct sockaddr);


		if((data_socket = accept(connection_socket, &remote, &len)) == -1){
			PEXIT("accept");
		}

		puts("Connected...");

		while(strcmp(*buff_ptr, "end") != 0){
			memset(*buff_ptr, '\0', BUFF_SIZE);

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
			}
		}
		
	}

	
	close(data_socket);
	close(connection_socket);
	unlink(myfifo);

	return 0;

}
