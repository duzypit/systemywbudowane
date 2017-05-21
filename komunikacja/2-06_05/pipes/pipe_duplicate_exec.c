/*
 * @author Marcin Kołodziej
 * @brief pipe two external programs example
 */

#include <stdio.h>
#include <string.h>

#include <stdlib.h> // exit
#include <unistd.h> // pipe, read, write

int main (int argc, char** argv) {
  int   fd[2];  // file descriptors
  pid_t cpid;   // child process id

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
    dup2(fd[1], 1); // duplicate pipe output to stdout
    execlp("ls", "ls", NULL);
    exit(0);
  }
  else {
    // parent process
    close(fd[1]);   // close output side of pipe
    dup2(fd[0], 0); // duplicate pipe input to stdin
    execlp("grep", "grep", "pipe", NULL);
  }

  return 0;
}
