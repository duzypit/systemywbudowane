/*
 * @author Marcin Kołodziej
 * @brief create pipe example
 */

#include <stdio.h>
#include <string.h>

#include <stdlib.h> // exit
#include <unistd.h> // pipe, read, write

int main (int argc, char** argv) {
  int   fd[2];  // file descriptors
  int   bytes;  // read bytes
  pid_t cpid;   // child process id
  char  msg[] = "Message from the other process via pipe!\n";
  char  readbuf[255];

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
    close(fd[0]);                         // close input side of pipe
    write(fd[1], msg, (strlen(msg) + 1)); // write message to pipe
    exit(0);
  }
  else {
    // parent process
    close(fd[1]); // close output side of pipe
    bytes = read(fd[0], readbuf, sizeof(readbuf));
    printf("Received string from child(pid %x): %s", cpid, readbuf);
  }

  return 0;
}
