//http://man7.org/linux/man-pages/man7/unix.7.html#EXAMPLE
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

#define PEXIT(str) {perror(str);exit(1);}
#define PCONT(str){perror(str);continue;}

#define PORT "3490"
#define MAXDATASIZE 100 //max number o bytes to get at once

//get sockaddr, IPv4 or IPv6
void * get_in_addr(struct sockaddr *sa){
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(int argc, char *argv[]){
	system("clear");

	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	
	if (argc != 2) {
		fprintf(stderr, "usage: client hostname\n");
		exit(1);
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
	
	if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1){
		PEXIT("recv");
	}
	buf[numbytes] = '\0';
	printf("client: received '%s'\n", buf);
	close(sockfd);
	
	
	
	return 0;
}
