#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

#define PEXIT(str) {perror(str);exit(1);}
#define PCONT(str){perror(str);continue;}

#define BUFF_SIZE 256
#define PORT "3490"
#define BACKLOG 10


void sigchld_handler(void){
	//waitpid() might overwrite errno, so we save and restore it:
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

int main(void){
	system("clear");
	//char * buff_ptr = calloc(sizeof(char) * BUFF_SIZE);
	char buffer[BUFF_SIZE] = {0};
	int sockfd, new_fd; //listen on sockfd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
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
*/
	struct sockaddr_storage their_addr; // connector's address information
/*
struct sockaddr_storage {
    sa_family_t  ss_family;     // address family
    // all this is padding, implementation specific, ignore it:
    char      __ss_pad1[_SS_PAD1SIZE];
    int64_t   __ss_align;
    char      __ss_pad2[_SS_PAD2SIZE];
};
*/

	socklen_t sin_size;
	struct sigaction sa;
/*
	struct sigaction {
		void     (*sa_handler)(int);
		void     (*sa_sigaction)(int, siginfo_t *, void *);
		sigset_t   sa_mask;
		int        sa_flags;
		void     (*sa_restorer)(void);
	};
*/
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my ip
	
	if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
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
	
	if (listen(sockfd, BACKLOG) == -1) {
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
		
		if(!fork()){ //this is the child process
			close(sockfd); //child doesn't need the listener
			if(send(new_fd, "hello world!",13, 0) == -1){
				perror("send");
				//close(new_fd);
				exit(0);
			}
			
			while(strcmp(buffer, "end") != 0){
					memset(buffer, 0, BUFF_SIZE);
					if(recv(new_fd, buffer, BUFF_SIZE, 0) == -1){
						PEXIT("read");
					}
					//sleep(1);			

					buffer[strcspn(buffer,"\r\n")] = 0;

					fprintf(stderr, "client: %s\n", buffer);

					//int i;
					//for(i = 0; i < (unsigned int) strlen(buffer); i++){
					//	fprintf(stderr, "%d : %c : %d\n", i+1, buffer[i], (int) buffer[i]);
					//}

					if(strcmp(buffer, "list if") == 0){
						struct ifaddrs *addrs, *tmp;
						if (getifaddrs(&addrs) == -1) {
							PEXIT("getiffaddrs");
						}
						tmp = addrs;
						memset(buffer, 0, BUFF_SIZE);
						while (tmp) 
						{
							if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
							{
								struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
								strncat(buffer, tmp->ifa_name, 10);
								strncat(buffer, ": ",2);
								strncat(buffer,inet_ntoa(pAddr->sin_addr),15);
								strncat(buffer, "\n",2);
								//printf("%s: %s\n", tmp->ifa_name, inet_ntoa(pAddr->sin_addr));
							}
							tmp = tmp->ifa_next;
						}
						
						freeifaddrs(addrs);
						puts(buffer);
					}
//if buffer not empty
					if(send(new_fd, buffer,sizeof(buffer), 0) == -1){
						perror("send");
						exit(0);
					}
					
					if(strcmp(buffer, "end") == 0){
						puts("End detected...");
						close(new_fd);
					}
				}			
			
			close(new_fd); // parent doesn't need this
			return 0;
		}
	} //end while(1)
	
	return 0;	
	
}