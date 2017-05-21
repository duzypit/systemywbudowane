/*
 * @author Marcin Kołodziej
 * @brief echo server using pipe
 */

#include <stdio.h>
#include <string.h>

#include <stdlib.h> // exit
#include <unistd.h> // pipe, read, write

int main (int argc, char** argv) {
  int   fd[2];  // file descriptors
  int   bytes;  // read bytes
  pid_t cpid;   // child process id
  char  readbuf[255];
  memset(readbuf, 0, sizeof(readbuf));

  pipe(fd);

  cpid = fork(); // file descriptors are inherited
                 // by child process

  if (cpid == -1) {
    // on error
    perror("fork");
    exit(1);
  }

  if (cpid == 0) {
    // child process
    close(fd[0]);   // close input side of pipe
    dup2(fd[1], 1); // duplicate pipe input to stdout

    while(scanf("%s", readbuf)) {
      if (strcmp(readbuf, "quit") != 0) {
        printf("%s", readbuf);
        fflush(stdout);
        memset(readbuf, 0, sizeof(readbuf));
      }
      else {
        break;
      }
    }

    exit(0);
  }
  else {
    // parent process
    close(fd[1]); // close output side of pipe
    while (bytes = read(fd[0], readbuf, sizeof(readbuf))) {
      if (strcmp(readbuf, "quit") != 0) {
        printf("Received string from child(pid %d): %s\n", cpid, readbuf);
      }
      else {
        break;
      }
      memset(readbuf, 0, sizeof(readbuf));
    }
  }

  return 0;
}
