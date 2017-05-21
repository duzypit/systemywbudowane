/*
 * @author Marcin Kołodziej
 * @brief Unix socket example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>  // ip

void error(char * msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    printf("Usage: %s [server|client]\n", argv[0]);
    exit(0);
  }

  struct sockaddr_in addr_server;
  struct sockaddr_in addr_client;
  int                addr_length = sizeof(addr_server);
  int                sockfd;
  char               buffer[256];
  int                bytes;

  // server code
  if (strcmp(argv[1], "server") == 0) {
    // create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == -1) {
      error("server socket");
    }

    // zero the address structs
    memset(&addr_server, 0, sizeof(addr_server));
    memset(&addr_client, 0, sizeof(addr_client));

    // set the server address structur
    // hton* functions convert values between host and network byte order
    addr_server.sin_family      = AF_INET;
    addr_server.sin_port        = htons(8888);
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
    // passing INADDR_ANY binds socket to all available interfaces

    // bind socket to port
    if (bind(sockfd, (struct sockaddr *) &addr_server, sizeof(addr_server)) == -1) {
      error("server bind");
    }

    // forever loop with datagram handling
    for (;;) {
      printf("Waiting for data... ");
      fflush(stdout);
      memset(buffer, 0, 256);
      
      // try to receive data, blocking call
      bytes = recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *) &addr_client, &addr_length);
      if (bytes == -1) {
        error("server recvfrom");
      }

      printf("[%s:%d (%d)] %s\n",
              inet_ntoa(addr_client.sin_addr),
              ntohs(addr_client.sin_port),
              addr_length,
              buffer);
      
      // reply with the same data
      if (sendto(sockfd, buffer, bytes, 0, (struct sockaddr *) &addr_client, addr_length) == -1) {
        printf("addr_length(%d)\n", addr_length);
        error("server sendto");
      }
    }
  }
  // client code
  else if(strcmp(argv[1], "client") == 0) {
    // create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == -1) {
      error("client socket");
    }

    // zero the address struct
    memset(&addr_server, 0, sizeof(addr_server));

    // set the server address struct
    // hton* functions convert values between host and network byte order
    addr_server.sin_family      = AF_INET;
    addr_server.sin_port        = htons(8888);

    // translate localhost address for struct
    if (inet_aton("127.0.0.1", &addr_server.sin_addr) == 0) {
      error("client inet_aton");
    }

    // forever loop sending messages with 1s interval
    for (;;) {
      char msg[] = "ECHO";

      // send the message
      if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *) &addr_server, addr_length) == -1) {
        error("client sendto");
      }

      // zero the receiving buffer
      memset(buffer, 0, 256);

      // try to read the response
      if (recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *) &addr_server, &addr_length) == -1) {
        error("client recvfrom");
      }

      printf("Reponse from server: %s\n", buffer);

      sleep(1);
    }

  }
  else {
    printf("Usage: %s [server|client]\n", argv[0]);
    exit(1);
  }

  return 0;
}