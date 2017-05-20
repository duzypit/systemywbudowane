/*
 * @author Marcin Kołodziej
 * @brief UDP socket example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h> // for AF_UNIX socket

void error(char * msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    printf("Usage: %s [server|client]\n", argv[0]);
    exit(0);
  }

  struct sockaddr_un sockaddr;
  socklen_t          addrlen = sizeof(sockaddr);
  int                sockfd;

  // zero the address structure before use
  memset(&sockaddr, 0, sizeof(struct sockaddr_un));
  sockaddr.sun_family = AF_UNIX;
  sprintf(sockaddr.sun_path, "/tmp/unix.socket");

  // server code
  if (strcmp(argv[1], "server") == 0) {
    int                connfd;
    pid_t              cpid;

    // delete unix_socket file to prevent errors
    printf("Deleting socket file...\n");
    unlink("/tmp/unix.socket");

    // create descriptor for UNIX socket stream
    printf("Creating socket...\n");
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
      error("server socket");
    }

    // bind socket descriptor to file
    printf("Binding socket...\n");
    if (bind(sockfd, (struct sockaddr *) &sockaddr, sizeof(struct sockaddr)) != 0) {
      error("server bind");
    }

    // listen on socket, queue of max 5 connections
    printf("Begin listening on socket...\n");
    if (listen(sockfd, 5) != 0) {
      error("server listen");
    }

    // loop that will accept connections and handle them in new processes
    // note that accept is blocking
    printf("Init successful, start accepting.\n");
    while ((connfd = accept(sockfd, (struct sockaddr *) &sockaddr, &addrlen)) > -1) {
      cpid = fork();

      if (cpid == 0) {
        // handle connection in child process
        char buffer[256];
        int  bytes = 0;

        // read from socket like from file
        bytes = read(connfd, buffer, 256);
        buffer[bytes] = 0;
        printf("Received message from client: %s\n", buffer);
        
        // send response to the client
        bytes = snprintf(buffer, 256, "Thank you for the message!");
        write(connfd, buffer, bytes);

        // close connection fd
        close(connfd);
        return 0;
      }

      // close connection fd in server process
      close(connfd);
    }

    // close descriptor and delete file
    close(sockfd);
    unlink("/tmp/unix.socket");
    error("accept");
  }
  // client code
  else if(strcmp(argv[1], "client") == 0) {
    char buffer[256];
    int  bytes = 0;

    // open socket
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
      error("client socket");
    }

    // connect to the opened socket
    if (connect(sockfd, (struct sockaddr *) &sockaddr, sizeof(struct sockaddr)) != 0) {
      printf("%s\n", sockaddr.sun_path);
      error("client connect");
    }

    // send message to the server
    bytes = snprintf(buffer, 256, "Hello from client!");
    write(sockfd, buffer, bytes);

    // check the response
    bytes = read(sockfd, buffer, 256);
    buffer[bytes] = 0;

    printf("Received message from server: %s\n", buffer);

    // close socket descriptor
    close(sockfd);
    exit(0);
  }
  else {
    printf("Usage: %s [server|client]\n", argv[0]);
    exit(1);
  }

  return 0;
}