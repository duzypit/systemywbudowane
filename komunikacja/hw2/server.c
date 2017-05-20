/*
 * @author Tomasz Piątek
 * @brief HW 06.05 - client/server chat - server
 */

#include <stdio.h>
#include <sys/types.h> //struct addrinfo, getaddrinfo, getpid, waitpid
#include <signal.h> //sigaction
#include <sys/socket.h> //struct addrinfo, getaddrinfo
#include <netdb.h> //struct addrinfo, getaddrinfo
#include <sys/wait.h> //waitpid
// #include <sys/un.h>
#include <string.h> //memset
#include <unistd.h> //close, getpid
#include <stdlib.h>// exit
#include <errno.h>
#include <arpa/inet.h>//inet_ntop
// #include <ifaddrs.h>
// #include <sys/ioctl.h>
// #include <linux/if.h>
/*
Treść zadania

Zaimplementować prosty "czat" międzyprocesowy.
    2. Serwer - przyjmuje połączenia, wypisuje następujące informacje na standardowe wyjście albo do pliku:
        1. Wypisuje następujące informacje na standardowe wyjście albo do pliku:
            1. Czas nadania wiadomości.
            2. Czas odebrania wiadomości.
            3. Identyfikator nadawcy.
            4. Wiadomość.
        2. Wysyła potwierdzenie odebrania wiadomości do klienta.
        3. Rozsyła otrzymane wiadomości do połączonych klientów. (* nadobowiązkowe)
*/

//------------------------------------------------MACROS
#define PEXIT(str) {perror(str);exit(1);}
#define PCONT(str) {perror(str);continue;}

//------------------------------------------------INTERFACES
#define BUFF_SIZE 512 //max number o bytes to get at once
#define PORT "3456"
#define MAX_CLIENTS 5

//------------------------------------------------PROTO
void sigchld_handler(void);
void * get_in_addr(struct sockaddr *sa);

//------------------------------------------------MAIN
int main(void){
	char * buffer = NULL;
	int sockfd, new_fd; //listen on sockfd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	pid_t pid;
	char * client_id;

	buffer = calloc(BUFF_SIZE, sizeof(char));
    

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my ip
	if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){ //
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	
	// loop throught all the results and bind to first we can
	for(p = servinfo; p != NULL; p = p->ai_next){
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
			PCONT("server: socket");
		}
		
		if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
			PEXIT("setscokopt");			
		}
		
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
			close(sockfd);
			PCONT("server: bind");
		}
		break;
	}
	
	freeaddrinfo(servinfo); //all done with this structure - network service & address translation
	
	if(p == NULL){
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
	
	//backlog = MAX_CLIENTS
	if (listen(sockfd, MAX_CLIENTS) == -1) {
		PEXIT("listen");
	}
	
	sa.sa_handler = sigchld_handler; //reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1){
		PEXIT("sigaction");
	}
	
	printf("server: waitning for connections...\n");
	
	while(1){ //main accept loop

		sin_size = sizeof(their_addr);
		new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if (new_fd == -1) {
			PCONT("accept");
		}

		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof(s));
		printf("server: got connection from %s\n",s);
		
		pid = fork();
		if(pid == 0){ //this is the child process

			close(sockfd); //child doesn't need the listener

			memset(buffer, 0, BUFF_SIZE);	
			if(recv(new_fd, buffer, BUFF_SIZE-1, 0) == -1){ //recieve data from client
				PEXIT("id read");
				exit(0);
			}

			printf("Recieved client id: %s\n", buffer);

			client_id = calloc(strlen(buffer), sizeof(char)); //set client id for this process
			memcpy(client_id, buffer, strlen(buffer));

			memset(buffer, 0, BUFF_SIZE);
			buffer = "Client ack";

			if(send(new_fd, buffer, strlen(buffer), 0) == -1){
				perror("id ack send");
				exit(0);
			}

			while(1){
				
				buffer = calloc(BUFF_SIZE, sizeof(char));
				if(recv(new_fd, buffer, BUFF_SIZE-1, 0) == -1){ //recieve data from client
					PEXIT("read");
				}

				
				buffer[strcspn(buffer,"\r\n")] = 0; //remove \r\n from msg
				printf("%s\n", buffer);

				
				if ((int)buffer[0] == 'q'){ //client quit
					printf("Client %s connection closed\n", client_id);
					free(buffer);
            		close(new_fd);	
            		exit(1);
				} else { //send ack


					memset(buffer, 0, BUFF_SIZE);
					buffer = "Message ack";
					if(send(new_fd, buffer,strlen(buffer), 0) == -1){
						perror("send");
						exit(0);
					}
				}
			} //while(1) end		

		} // close if(pid ==0 )

		close(new_fd); // parent doesn't need accept socket
	} //end while(1)
	return 0;
}

//------------------------------------------------FUNCS
//waitpid() might overwrite errno, so we save and restore it:
void sigchld_handler(void){
	
	int saved_errno = errno;
	while(waitpid(-1, NULL, WNOHANG) >0);
	errno = saved_errno;
}

//get sockaddr, IPv4 or IPv6
void * get_in_addr(struct sockaddr *sa){
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}