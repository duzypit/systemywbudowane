/*
 * @author Tomasz Piątek
 * @brief HW 06.05 - client/server chat - client
 */

#include <stdio.h>
//#include <sys/un.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <errno.h>
//#include <string.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>

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
#define PCONT(str){perror(str);continue;}

//------------------------------------------------DEF
#define BUFF_SIZE 512 //max number o bytes to get at once

//------------------------------------------------INTERFACES


//------------------------------------------------MAIN
int main(void){
	char * buffer = NULL;
	int sockfd, numbytes, rv;
	struct addrinfo hints, *servinfo, *p;
	char s[INET6_ADDRSTRLEN];


	if (argc < 2){
		printf("Usage: %s host \n", argv[0]);
		exit(0);
	}

	return 0;
}

//------------------------------------------------FUNCS