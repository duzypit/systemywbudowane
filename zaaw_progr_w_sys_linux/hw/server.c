/*
 * @author Tomasz Piątek
 * @brief socet connection - client
 */

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

//------------------------------------------------MACRO
#define PEXIT(str) {perror(str);exit(1);}
#define PCONT(str){perror(str);continue;}

//------------------------------------------------DEF
#define BUFF_SIZE 256
#define DELIM " -\t\r\n\a"
#define CDELIM "="

typedef struct config{
	char * ptr_port;
	int max_clients;
} config;
//------------------------------------------------GLOBALS

//------------------------------------------------PROTO
void sigchld_handler(void);
void * get_in_addr(struct sockaddr *sa);
char * list_int();
void print_char(char * s); //util
char * if_ipv4(char * interface);
char * if_up(char * interface);
char * mac(char *interface);
char * change_ip(char *interface, char *a);
char * dispatcher(char * buffer);
struct config load_cfg(char * fname);
void ptr_print_col(char * ptr); //util
//------------------------------------------------MAIN
int main(int argc, char **argv){

	char * buffer = NULL;
	int sockfd, new_fd; //listen on sockfd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	int ccount = 0; //children count, cant fork if ccount = cfg.max_clients

	if (argc < 2){
		printf("Usage: %s config_file_name\n", argv[0]);
		exit(0);
	}

	//what if no file??
	config cfg = load_cfg(argv[1]);

	printf("Config.port: %s\n",cfg.ptr_port);
	printf("Config.max_clients: %d\n",cfg.max_clients);
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my ip
	if((rv = getaddrinfo(NULL, cfg.ptr_port, &hints, &servinfo)) != 0){ //
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	
	// loop throught all the results and bind to first we can
	for(p = servinfo; p != NULL; p = p->ai_next){
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
			PCONT("Server: socket");
		}
		
		if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
			PEXIT("setscokopt");			
		}
		
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
			close(sockfd);
			PCONT("Server: bind");
		}
		break;
	}
	
	freeaddrinfo(servinfo); //all done with this structure - network service & address translation
	
	if(p == NULL){
		fprintf(stderr, "Server: failed to bind\n");
		exit(1);
	}
	
	//backlog = cfg max_clients
	if (listen(sockfd, cfg.max_clients) == -1) {
		PEXIT("listen");
	}
	
	sa.sa_handler = sigchld_handler; //reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1){
		PEXIT("sigaction");
	}
	
	printf("Server: waitning for connections...\n");

	//free config ptr, dont need it anymore
	free(cfg.ptr_port);

	while(1){ //main accept loop

		while(ccount >= cfg.max_clients){ //loop to control amount of forked processes
			int status;
			if(wait(&status) >= 0) {
				ccount--;
			}
		}

		sin_size = sizeof(their_addr);
		new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if (new_fd == -1) {
			PCONT("accept");
		}
	
		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof(s));
		printf("Server: got connection from %s\n",s);

	
		pid_t pid = fork(); 
		ccount++;

		if(pid == 0){ //this is the child process
			//sleep(10);
			pid_t cpid = getpid();
			close(sockfd); //child doesn't need the listener
			buffer = calloc(BUFF_SIZE, sizeof(char)); //first use of buffer, fill with 0s;
			sprintf(buffer, "%d",cpid);
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

					char * result = NULL;

					//client quit
					if ((int)buffer[0] == 'q' && strlen(buffer) == 1){
						puts("Connection terminated by client");
						free(buffer);
						free(result);
                		close(new_fd);	
                		exit(0);
					}
					//parse commands block and return value;
					result = dispatcher(buffer);
					printf("\tMsg: %s\n", result);
					//send return msg
					if(send(new_fd, result,BUFF_SIZE, 0) == -1){
						perror("send");
						exit(0);
					}
					free(result);
				}			
			
			close(new_fd); // parent doesn't need this
			return 0;
		}
	} //end while(1)
	close(new_fd); // parent doesn't need this
	return 0;	
	
}

//------------------------------------------------FUNCS
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

char * list_int(){
    struct ifaddrs *addrs, *tmp;
    if (getifaddrs(&addrs) == -1) {
        PEXIT("getiffaddrs");
    }
    tmp = addrs;
    char * buffer = calloc(BUFF_SIZE, sizeof(char));
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
	char * result = NULL;
    result = calloc(BUFF_SIZE, sizeof(char));
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
	result = calloc(BUFF_SIZE, sizeof(char));
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
    result = calloc(BUFF_SIZE, sizeof(char));
    if(ethreq.ifr_flags & IFF_LOOPBACK){
       sprintf(result,"NO mac address for %s - loopback", interface);
    } else {
        ioctl(fd, SIOCGIFHWADDR, &ethreq);
        sprintf(result,"Device %s -> mac: %02x:%02x:%02x:%02x:%02x:%02x\n", interface,
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
    result = calloc(BUFF_SIZE, sizeof(char));
    sprintf(result, "Ipv4 address set to: %s\n", a);
    return(result);
}

char * dispatcher(char * buffer){
	//char * result = malloc(BUFF_SIZE * sizeof(char));	
	char * result = NULL;
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
            	//list all ifs
            	result = list_int();
                break;
            case 'i':
            	//assign expected if to var
                if(tokens[i]  != NULL){  
                    interface = tokens[++i];
                }
                break;
            case 'a':
            	//printf("change IPv4 addr to given");
               //change IPv4 addr to given
                    if(interface != NULL){
                        result = change_ip(interface, tokens[++i]);
                    }                
                break;
            case 's' :
                //show status for selected if
            		if(interface != NULL){
            			result = if_up(interface);
            		}
                break;
            case 'h':
                //show mac for selected if
                    if(interface != NULL){
                    	result = mac(interface);   
                    }
                break;
            case '4':
                //show ipv4 + mask for selected if
                if (interface != NULL){
                    result = if_ipv4(interface);
                }
                break;
            default:
            	result = calloc(BUFF_SIZE, sizeof(char));	
                sprintf(result,"%s", "No such option!");
        }        
    }

    //result is null ie. i lo command without third arg
    if(result == NULL){
    	result = calloc(BUFF_SIZE, sizeof(char));	
        sprintf(result,"%s", "No such option!");    	
    }

    //destroy tokens array;
    free(tokens);
    return result;	
}

struct config load_cfg(char * fname){
	config result;
	FILE * file = fopen(fname, "r");

	if(file != NULL){
		char line[BUFF_SIZE];
		int i = 0;
		while(fgets(line, sizeof(line), file) != NULL){
			char *cfline;
			
			cfline = strstr((char*)line, CDELIM);
			cfline = cfline + strlen(CDELIM);
			cfline[strcspn(cfline,"\r\n")] = 0;
			if (i == 0){
				result.ptr_port = calloc(strlen(cfline)+1, sizeof(char));
				sprintf(result.ptr_port, "%s", cfline);
			} else if (i == 1){
				result.max_clients = atoi(cfline);
			}
			i++;
		} // end while
		fclose(file);
	} else {
		PEXIT("No file");
	}
	return result;
}

void ptr_print_col(char * ptr){
	int i = 0;
	while(ptr[i] != '\0'){
		printf("i: %d, c: %c\n", (int) ptr[i], (char)ptr[i]);
		i++;
	}
}
