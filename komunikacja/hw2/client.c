/*
 * @author Tomasz Piątek
 * @brief HW 06.05 - client/server chat - client
 */

#include <stdio.h>
#include <sys/types.h> //struct addrinfo, getaddrinfo, getpid, watipid
#include <sys/socket.h> //struct addrinfo, getaddrinfo
#include <netdb.h> //struct addrinfo, getaddrinfo
#include <unistd.h> //close, getpid
#include <stdlib.h>// exit
#include <errno.h>
#include <string.h> //memset
#include <netinet/in.h>//sockaddr_in6
#include <arpa/inet.h>//inet_ntop
#include <time.h> //time & co.
#include <signal.h> //sigaction, sigemptyset

/*
Treść zadania

Zaimplementować prosty "czat" międzyprocesowy.
    1. Klient - łączy się wybranym sposobem z serwerem, przesyła mu wiadomości zawierające następujące dane:
        1. Czas nadania wiadomości.
        2. Identyfikator nadawcy.
        3. Wiadomość.
*/

//------------------------------------------------MACROS
#define PEXIT(str) {perror(str);exit(1);}
#define PCONT(str) {perror(str);continue;}

//------------------------------------------------DEF
#define BUFF_SIZE 512 //max number o bytes to get at once
#define PORT "3456"

//------------------------------------------------PROTO
void * get_in_addr(struct sockaddr *sa);
char * get_time(void);
char * format_msg(char * msg);


//------------------------------------------------MAIN
int main(int argc, char **argv){
	char * buffer = NULL;
    char * fbuffer = NULL;
    //init
    buffer = calloc(BUFF_SIZE, sizeof(char));

	int sockfd, 
		numbytes, 
		rv;
	
	struct addrinfo hints, 
					*servinfo, 
					*p;

	char s[INET6_ADDRSTRLEN];

	if (argc < 2){
		printf("Usage: %s host \n", argv[0]);
		exit(0);
	}

	memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    //int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
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


    pid_t pid = getpid();
    memset(buffer, 0, BUFF_SIZE);
    sprintf(buffer, "%d", pid);

    //send my id, 
    if((send(sockfd, buffer, sizeof(buffer), 0)) == -1){
        PEXIT("send pid");
    }    

    printf("Client id: %s\n", buffer);

    //recieveack
    memset(buffer, 0, BUFF_SIZE);
    if((numbytes = recv(sockfd, buffer, BUFF_SIZE, 0)) == -1){
        PEXIT("recv");
    }
    printf("Server: %s\n", buffer);
    printf("q - quit\n");

    //fbuffer = calloc(BUFF_SIZE, sizeof(char));
    while(1){
		printf(">: ");

        memset(buffer, 0, BUFF_SIZE);        
        fgets(buffer, BUFF_SIZE, stdin);
        buffer[strcspn(buffer,"\r\n")] = 0;

        //memset(fbuffer, 0, BUFF_SIZE);
        //fbuffer = NULL;
        //fbuffer = 
        buffer = format_msg(buffer);
        printf("\tYou: %s\n",buffer);

		if((send(sockfd, buffer, BUFF_SIZE, 0)) == -1){
     		PEXIT("send");
        }

        //quit
        if((int)buffer[10] == 'q'){
            free(buffer);
            free(fbuffer);
            close(sockfd);  
            puts("Bye!");
            exit(0);
        } else {
            memset(buffer, 0, BUFF_SIZE);
            if((recv(sockfd, buffer, BUFF_SIZE, 0)) == -1){
                    PEXIT("read");
            }
            printf("\tServer: %s\n", buffer);            
        }

      
    } // end while

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

char * get_time(void){
    time_t t;
    struct tm *timeinfo;
    char * result = calloc(10, sizeof(char));

    time(&t);
    timeinfo = localtime(&t);
    //%F -data
    strftime(result,10,"%H:%M:%S",timeinfo);
    //free(timeinfo);
    return(result);
}

char * format_msg(char * msg){
    char * tmp_msg = calloc(strlen(msg)+1, sizeof(char));
    memcpy(tmp_msg, msg, strlen(msg));

    memset(msg, 0, BUFF_SIZE);
    char * t = NULL;
    t = get_time();
    
    sprintf(msg, "%s: %s", t, tmp_msg);
    
    free(t);
    free(tmp_msg);
    
    return(msg);
}
/*
char * format_msg_old(char * msg){
    //char * tmp_msg = msg;
    //calloc(BUFF_SIZE, sizeof(char));
    memset(msg, 0, BUFF_SIZE);
    char * t = calloc(26, sizeof(char));
    t = get_time();

    sprintf(msg, "%s: %s", t, tmp_msg);
    free(t);
    free(tmp_msg);
    return(tmp_msg);
}
*/