#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//ifaddr
#include <sys/types.h>
#include <sys/socket.h>
//freeifaddrs
#include <ifaddrs.h>
//inet_ntoa
#include <netinet/in.h>
#include <arpa/inet.h>
//ioctl
#include <sys/ioctl.h>
#include <linux/if.h>

#define BUFSIZE 256
#define DELIM " -\t\r\n\a"
#define PEXIT(str) {perror(str);exit(1);}
//http://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array
//http://man7.org/linux/man-pages/man3/getopt.3.html
//https://brennan.io/2015/01/16/write-a-shell-in-c/
//http://stackoverflow.com/questions/4936052/what-are-the-network-ioctl-man-pages
//https://www.google.pl/search?q=network+interface+ioctl&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=DmD3WKD6GeWP8QfZ9oL4AQ
//http://www.linuxquestions.org/questions/linux-networking-3/ioctl-and-changing-network-interface-flags-751709/
//usr/include/net/if.h
//http://www.microhowto.info/howto/get_the_ip_address_of_a_network_interface_in_c_using_siocgifaddr.html

//new links
//https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/apis/getifaddrs.htm
//http://www.binarytides.com/c-program-to-get-ip-address-from-interface-name-on-linux/
//http://man7.org/linux/man-pages/man7/netdevice.7.html
char * list_int(char * buffer){
    struct ifaddrs *addrs, *tmp;
    if (getifaddrs(&addrs) == -1) {
        PEXIT("getiffaddrs");
    }
    tmp = addrs;
    memset(buffer, 0, BUFSIZE);
    while (tmp) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET) {
            //printf("len: %lu\n", strlen(tmp->ifa_name));
            strncat(buffer, tmp->ifa_name, 10);
            strncat(buffer, "\n",2);
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
    char * buffer = calloc(BUFSIZE, sizeof(char));
    struct ifaddrs *addrs, *tmp;
    if (getifaddrs(&addrs) == -1) {
        PEXIT("getiffaddrs");
    }
    tmp = addrs;
    //memset(buffer, 0, BUFSIZE);
    while (tmp) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET && (!strcmp(interface, tmp->ifa_name))){
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            strncat(buffer,inet_ntoa(pAddr->sin_addr),15);
            strncat(buffer, ": ",2);
            struct sockaddr_in *pNetm = (struct sockaddr_in *)tmp->ifa_netmask;
            strncat(buffer,inet_ntoa(pNetm->sin_addr),15);
            strncat(buffer, "\n",2);
            
        }
        tmp = tmp->ifa_next;
    }
    
    freeifaddrs(addrs);
    return buffer;     
}

void if_up(char * interface){
	int fd = socket(PF_INET, SOCK_STREAM,0 );
	struct ifreq ethreq;
	memset(&ethreq, 0, sizeof(ethreq));
	strncpy(ethreq.ifr_name, interface, IFNAMSIZ);	
	ioctl(fd, SIOCGIFFLAGS, &ethreq);
	if(ethreq.ifr_flags & IFF_UP){
		printf("%s is UP\n", ethreq.ifr_name);
	} else {
		printf("%s is DOWN\n", ethreq.ifr_name);
	}
	close(fd);
}

/*
void mac(char *interface){
	int fd = socket(PF_INET, SOCK_STREAM,0);
	struct irfeq ethreq;
	memset(ethreq, 0, sizeog(ethreq));
	strncpy(ethreq.ifr_name, interface,IFNAMSIZ);
	
}
*/
int main(int argc, char *argv[]){
    char buffer[BUFSIZE] = {0};
    char **tokens = malloc(BUFSIZE * sizeof(char*));
    char *token;
    tokens[0] = argv[0];
while(1){
    printf(">: ");
    memset(buffer, 0, BUFSIZE);
	fgets(buffer, sizeof(buffer), stdin);
	//buffer[strcspn(buffer,"\r\n")] = 0;
    
    int position = 1;
    tokens[0] = argv[0];
    
    token = strtok(buffer, DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;
    
        token = strtok(NULL, DELIM);
    }
    //free(token);
    //tokens[position] = "-1";

    char * interface = NULL;
    int i = 0;
    for(i = 1; i < position; i++){
        //printf("%s\n", tokens[i]);
        switch(*tokens[i]) {
            case 'l':
                printf("%s",list_int(buffer));
                break;
            case 'i':
                printf("selected if: %s\n", tokens[++i]);
                if(tokens[i]  != NULL){  
                    interface = tokens[i];
                    //printf("len: %lu\n", strlen(interface));
                }
                break;
            case 'a':
                puts("show all for selected interface");
                break;
            case 's' :
                puts("show status for selected if");
		if(interface != NULL){
			if_up(interface);
		}
                break;
            case 'm':
                puts("show mac for selected if");
			
                break;
            case '4':
                //puts("show ipv4 + mask for selected if");
                if (interface != NULL){
                    //printf("if: %s\n", interface);
                    printf("%s",if_ipv4(interface));
                }
                break;
            case '6':
                puts("show ipv4 + mask for selected if");
                break;
            case 'u':
                puts("selected if up");
                break;
            case 'd':
                puts("selected if down");
                break;
            default:
                printf("no such option: %s\n", tokens[i]);
                //fprintf(stderr, "Usage: %s [l] [-i if] [asm46]\n", argv[0]);
                //exit(EXIT_FAILURE);
        }        
    }
    
/*    
    int opt;
    while((opt = getopt(position, tokens, "li:asm46")) != -1)
        //printf("c = %c (%d)\n",(char) opt, opt);
        switch(opt) {
            case 'l':
                puts("list");
                break;
            case 'i':
                printf("set interface: %s\n", optarg);
                break;
            case 'a':
                puts("show all for selected interface");
                break;
            case 's' :
                puts("show status for selected if");
                break;
            case 'm':
                puts("show mac for selected if");
                break;
            case '4':
                puts("show ipv4 + mask for selected if");
                break;
            case '6':
                puts("show ipv4 + mask for selected if");
                break;
            default:
                printf("opt: %d\n", opt);
                fprintf(stderr, "Usage: %s [l] [-i if] [asm46]\n", argv[0]);
                //exit(EXIT_FAILURE);
        }
    
    //free(tokens);
*/
}    
    return 0;
}
