/*
 * @author Tomasz Piątek
 * @brief socet connection - client
 */
#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//------------------------------------------------MACRO
#define PEXIT(str) {perror(str);exit(1);}
#define PCONT(str){perror(str);continue;}

//------------------------------------------------DEF
#define PORT "3490"
#define BUFF_SIZE 256 //max number o bytes to get at once

//------------------------------------------------GLOBALS

//------------------------------------------------PROTO
void * get_in_addr(struct sockaddr *sa);

//------------------------------------------------MAIN
int main(int argc, char **argv){
	
	char buffer[BUFF_SIZE] = {0};
	int sockfd, numbytes;

	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	
	if (argc < 2){
		printf("Usage: %s host \n", argv[0]);
		exit(0);
	}
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return(1);
	}
	
	//loop throught all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next){
		if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
			PCONT("client: socket");
		}
		
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1){
			close(sockfd);
			PCONT("client: connect");
		}
		break;
	} // for end
	
	if(p == NULL){
		fprintf(stderr, "clinet: failed to connect\n");
		return(2);
	}
	
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof(s));
	printf("client: connecting to %s\n", s);
	freeaddrinfo(servinfo); // all done with this str
	
	if((numbytes = recv(sockfd, buffer, BUFF_SIZE, 0)) == -1){
		PEXIT("recv");
	}
	
	printf("client: received %s\n", buffer);
	printf("? - help, q - quit\n");
	while(1){
		printf(">: ");
		memset(buffer, 0, BUFF_SIZE);
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer,"\r\n")] = 0;
				
		switch((int)buffer[0]){
            case '?':
            	//help - move this section to client
                printf("\nCommands:\n"
                    "q - exit\n"
                    "l - list ifs\n\n"
                    "i <if_name> x - select if and then execute x command\n\n"
                    "x may be:\n"
                    "s - show if status\n"
                    "h - show if hwaddr\n"
                    "4 - show if IPv$ addr : netmask\n\n"
                    "a <ip_v4_addr>  - change addr\n"

                    );
                break;
            default:
				if((send(sockfd, buffer, strlen(buffer), 0)) == -1){
					PEXIT("send");
				}
				
				//quit
                if((int)buffer[0] == 'q'){
                	puts("\tBye!");
                	close(sockfd);	
                	exit(0);
                }

				memset(buffer, 0, BUFF_SIZE);

				if((recv(sockfd, buffer, BUFF_SIZE, 0)) == -1){
					PEXIT("read");
				}
				printf("\tServer: %s\n", buffer);            
		}
	}	
	

	return 0;
}

//------------------------------------------------FUNCS
//get sockaddr, IPv4 or IPv6
void * get_in_addr(struct sockaddr *sa){
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}