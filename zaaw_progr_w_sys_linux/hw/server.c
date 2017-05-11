#include <stdio.h>
#include <sys/types.h> //getaddrinfo
#include <sys/wait.h>
#include <sys/socket.h> //getaddrinfo
#include <netdb.h> //getaddrinfo
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <linux/if.h>

#define PEXIT(str) {perror(str);exit(1);}
#define PCONT(str){perror(str);continue;}

#define BUFF_SIZE 256
#define PORT "3490"
#define BACKLOG 10
#define DELIM " -\t\r\n\a"


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

char * list_int(char * buffer){
    struct ifaddrs *addrs, *tmp;
    if (getifaddrs(&addrs) == -1) {
        PEXIT("getiffaddrs");
    }
    tmp = addrs;
    memset(buffer, 0, BUFF_SIZE);
    while (tmp) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET) {
            strncat(buffer, tmp->ifa_name, 10);
            strncat(buffer, " ",1);
        }
        tmp = tmp->ifa_next;
    }
    
    freeifaddrs(addrs);
    return buffer;    
}

void print_char(char * s){
    while(*s != '\0'){
        printf("%c : %d\n", *s, (int)*s);
        s++;
    }
    puts("---");
}

char * if_ipv4(char * interface){
    char * result = calloc(BUFF_SIZE, sizeof(char));
    struct ifaddrs *addrs, *tmp;
    if (getifaddrs(&addrs) == -1) {
        PEXIT("getiffaddrs");
    }
    tmp = addrs;
    while (tmp) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET && (!strcmp(interface, tmp->ifa_name))){
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            strncat(result,inet_ntoa(pAddr->sin_addr),15);
            strncat(result, " ",1);
            struct sockaddr_in *pNetm = (struct sockaddr_in *)tmp->ifa_netmask;
            strncat(result,inet_ntoa(pNetm->sin_addr),15);
            strncat(result, " ",1);
        }
        tmp = tmp->ifa_next;
    }
    freeifaddrs(addrs);
    return result;     
}

char * if_up(char * interface){
	int fd = socket(PF_INET, SOCK_STREAM,0 );
	struct ifreq ethreq;
	memset(&ethreq, 0, sizeof(ethreq));
	strncpy(ethreq.ifr_name, interface, IFNAMSIZ);	
	ioctl(fd, SIOCGIFFLAGS, &ethreq);
	char * result = NULL;
	if(ethreq.ifr_flags & IFF_UP){
		sprintf(result, "%s is UP\n", ethreq.ifr_name);
	} else {
		sprintf(result, "%s is DOWN\n", ethreq.ifr_name);
	}
	close(fd);
	return(result);
}


char * mac(char *interface){
	int fd = socket(PF_INET, SOCK_DGRAM,0);
	struct ifreq ethreq;
	memset(&ethreq, 0, sizeof(ethreq));
	strncpy(ethreq.ifr_name, interface, IFNAMSIZ);
    ioctl(fd, SIOCGIFFLAGS, &ethreq);

    char * result = NULL;
    if(ethreq.ifr_flags & IFF_LOOPBACK){
       sprintf(result,"NO mac address for %s - loopback\n", interface);
    } else {
        ioctl(fd, SIOCGIFHWADDR, &ethreq);
        sprintf(result,"Device %s -> Ethernet %02x:%02x:%02x:%02x:%02x:%02x\n", interface,
                (unsigned char)ethreq.ifr_hwaddr.sa_data[0],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[1],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[2],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[3],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[4],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[5]);
    }
    close(fd);
    return(result);
}

char * change_ip(char *interface, char *a){
	int fd = socket(PF_INET, SOCK_STREAM,0);
	struct ifreq ethreq;
	memset(&ethreq, 0, sizeof(ethreq));    
	strncpy(ethreq.ifr_name, interface, IFNAMSIZ);
    ethreq.ifr_addr.sa_family = AF_INET;
    struct sockaddr_in* addr = (struct sockaddr_in*)&ethreq.ifr_addr;
    inet_pton(AF_INET, a, &addr->sin_addr);
    ioctl(fd, SIOCSIFADDR, &ethreq);
    close(fd); 

    char * result = NULL;
    sprintf(result, "Ipv4 set to: %s\n", a);
    return(result);
}

// void change_netmask(char *interface, char *m){
    //http://stackoverflow.com/questions/6652384/how-to-set-the-ip-address-from-c-in-linux
// }

char * dispatcher(char * buffer){
	printf("Hi, i'm dispatcher\n");
	char **tokens = malloc(BUFF_SIZE * sizeof(char*));
    char *token;
    int position = 0;
    char * interface = NULL;

    token = strtok(buffer, DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;
        token = strtok(NULL, DELIM);
    }

    
    int i = 0;
    for(i = 0; i < position; i++){
        switch(*tokens[i]) {
            case 'l':
                //fprintf(stdout, "%s", list_int(buffer));
            	//list all ifs
            	return(list_int(buffer));
                break;
            case 'i':
                //printf("selected if: %s\n", tokens[++i]);
            	//assign expected if to var
                if(tokens[i]  != NULL){  
                    interface = tokens[i];
                }
                break;
            // case 'a':
            // 	//printf("change IPv4 addr to given");
            //    //change IPv4 addr to given
            //         if(interface != NULL){
            //             return(change_ip(interface, tokens[++i]));
            //         }                
            //     break;
            // case 's' :
            // 	//puts("show status for selected if");
            //     //show status for selected if
            // 		if(interface != NULL){
            // 			return(if_up(interface));
            // 		}
            //     break;
            // case 'm':
            // 	//puts("show mac for selected if");
            //     //show mac for selected if
            //         if(interface != NULL){
            //         	return(mac(interface));   
            //         }
            //     break;
            case '4':
            	//return("show ipv4 + mask for selected if");
                //show ipv4 + mask for selected if
                if (interface != NULL){
                    return(if_ipv4(interface));
                }
                break;
            // case 'u':
            //     return("set selected if up");
            //     break;
            // case 'd':
            //     return("set selected if down");
            //     break;
            default:
                return("No such option!");
        }        
    }	
}

	// struct addrinfo {
	// 	int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
	// 	int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
	// 	int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
	// 	int              ai_protocol;  // use 0 for "any"
	// 	size_t           ai_addrlen;   // size of ai_addr in bytes
	// 	struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
	// 	char            *ai_canonname; // full canonical hostname
	// 	struct addrinfo *ai_next;      // linked list, next node
	// };


	// struct sockaddr_storage {
	//     sa_family_t  ss_family;     // address family
	//     // all this is padding, implementation specific, ignore it:
	//     char      __ss_pad1[_SS_PAD1SIZE];
	//     int64_t   __ss_align;
	//     char      __ss_pad2[_SS_PAD2SIZE];
	// };


	// struct sigaction {
	// 	void     (*sa_handler)(int);
	// 	void     (*sa_sigaction)(int, siginfo_t *, void *);
	// 	sigset_t   sa_mask;
	// 	int        sa_flags;
	// 	void     (*sa_restorer)(void);
	// };

void ptr_print_col(char * ptr){
	int i = 0;
	while(ptr[i] != '\0'){
		printf("i: %d, c: %c\n", (int) ptr[i], (char)ptr[i]);
		i++;
	}
}

int main(void){
	//system("clear");
	char buffer[BUFF_SIZE] = {0};
	int sockfd, new_fd; //listen on sockfd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	
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
	
		pid_t pid = fork(); 
		if(pid == 0){ //this is the child process
			sleep(10);
			pid_t cpid = getpid();
			close(sockfd); //child doesn't need the listener
			
			sprintf(buffer, "%s %d", buffer, cpid);
			if(send(new_fd, buffer,sizeof(buffer), 0) == -1){
				perror("send");
				exit(0);
			}

			
			while(1){
					//fill buff with 0s
					memset(buffer, 0, BUFF_SIZE);

					//recieve data from client
					if(recv(new_fd, buffer, BUFF_SIZE, 0) == -1){
						PEXIT("read");
					}

					//remove \r\n from msg
					buffer[strcspn(buffer,"\r\n")] = 0;

					//write msg to stderr
					fprintf(stderr, "client %d: %s\n",cpid, buffer);
					//ptr_print_col(buffer);
					//parse commands block and return value;
					char * result = calloc(BUFF_SIZE, sizeof(char));

					result = dispatcher(buffer);
					puts(result);

					//send return msg
					if(send(new_fd, result,BUFF_SIZE, 0) == -1){
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
	close(new_fd); // parent doesn't need this
	return 0;	
	
}