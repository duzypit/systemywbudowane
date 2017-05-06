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
//https://www.google.pl/search?q=network+interface+ioctl&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=DmD3WKD6GeWP8QfZ9oL4AQ
//http://www.linuxquestions.org/questions/linux-networking-3/ioctl-and-changing-network-interface-flags-751709/
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


void mac(char *interface){
	int fd = socket(PF_INET, SOCK_DGRAM,0);
	struct ifreq ethreq;
	memset(&ethreq, 0, sizeof(ethreq));
	strncpy(ethreq.ifr_name, interface, IFNAMSIZ);
    ioctl(fd, SIOCGIFFLAGS, &ethreq);

    if(ethreq.ifr_flags & IFF_LOOPBACK){
       printf("NO mac address for %s - loopback\n", interface);
    } else {
        ioctl(fd, SIOCGIFHWADDR, &ethreq);
        //unsigned char* mac = (unsigned char*)ethreq.ifr_hwaddr.sa_data;
        //printf("%02X:%02X:%02X:%02X:%02X:%02X", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    printf("Device %s -> Ethernet %02x:%02x:%02x:%02x:%02x:%02x\n", interface,
                (unsigned char)ethreq.ifr_hwaddr.sa_data[0],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[1],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[2],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[3],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[4],
                (unsigned char)ethreq.ifr_hwaddr.sa_data[5]);
    }

    close(fd);
}

void ip(char *interface, char *addr){
	int fd = socket(PF_INET, SOCK_STREAM,0);
	struct ifreq ethreq;
	memset(&ethreq, 0, sizeof(ethreq));    
	strncpy(ethreq.ifr_name, interface, IFNAMSIZ);
    ethreq.ifr_addr.sa_family = AF_INET;
    
    struct scokaddr_in* sin;
    inet_pton(AF_INET, addr, a->sin_addr);
    ioctl(fd, SIOCSIFADDR, &ethreq);
    printf("Ipv4 set to: %s\n", addr);
    close(fd);
 struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
 printf("IP address: %s\n",inet_ntoa(ipaddr->sin_addr));
}

int main(int argc, char *argv[]){
    char buffer[BUFSIZE] = {0};
    char **tokens = malloc(BUFSIZE * sizeof(char*));
    char *token;
    tokens[0] = argv[0];
while(1){
    printf(">: ");
    memset(buffer, 0, BUFSIZE);
	fgets(buffer, sizeof(buffer), stdin);
    
    int position = 1;
    tokens[0] = argv[0];
    
    token = strtok(buffer, DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;
    
        token = strtok(NULL, DELIM);
    }

    char * interface = NULL;
    int i = 0;
    for(i = 1; i < position; i++){
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
                    if(interface != NULL){
                     mac(interface);   
                    }
                break;
            case '4':
                //puts("show ipv4 + mask for selected if");
                if (interface != NULL){
                    printf("%s",if_ipv4(interface));
                }
                break;
            case 'u':
                puts("set selected if up");
                break;
            case 'd':
                puts("set selected if down");
                break;
            default:
                printf("no such option: %s\n", tokens[i]);
        }        
    }
    
}    
    return 0;
}
