/*
 * @author Marcin Kołodziej
 * @brief use existing FIFO example
 */

#include <stdio.h>

#include <stdlib.h>    // exit
#include <unistd.h>    // read,write
#include <sys/types.h> // open
#include <sys/stat.h>  // mkfifo
#include <fcntl.h>     // open flags

int main (int argc, char** argv) {
  int   fd;     // file descriptor
  int   bytes;  // read bytes
  pid_t cpid;   // child process id
  char  msg[] = "Message from the other process via FIFO!\n";
  char  path[255];
  char  readbuf[255];

  if (argc < 2) {
    printf("Not enough arguments!\n");
    return 1;
  }

  strcpy(path, argv[1]);
  cpid = fork();

  if (cpid == -1) {
    // on error
    perror("fork");
    exit(1);
  }

  if (cpid == 0) {
    // child process
    fd = open(path, O_WRONLY);

    if (fd == -1) {
      printf("Child error: Cannot open file %s.\n", path);
      exit(1);
    }

    write(fd, msg, strlen(msg) + 1);
    close(fd);
    exit(0);
  }
  else {
    // parent process
    fd = open(path, O_RDONLY);

    if (fd == -1) {
      printf("Parent error: Cannot open file %s.\n", path);
      exit(1);
    }

    bytes = read(fd, readbuf, sizeof(readbuf));
    close(fd);
    printf("Received string from child(pid %x): %s", cpid, readbuf);
  }

  return 0;
}
