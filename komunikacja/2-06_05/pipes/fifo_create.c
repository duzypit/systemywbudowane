/*
 * @author Marcin Kołodziej
 * @brief FIFO mkfifo example
 */

#include <stdio.h>
#include <string.h>

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
  char  path[] = "/tmp/example_fifo";
  char  readbuf[255];

  mkfifo(path, 0666); // create fifo
                      // 666 == rw-rw-rw-

  cpid = fork();

  if (cpid == -1) {
    // on error
    perror("fork");
    exit(1);
  }

  if (cpid == 0) {
    // child process
    fd = open(path, O_WRONLY);
    write(fd, msg, strlen(msg) + 1);
    close(fd);
    exit(0);
  }
  else {
    // parent process
    fd = open(path, O_RDONLY);
    bytes = read(fd, readbuf, sizeof(readbuf));
    close(fd);
    printf("Received string from child(pid %x): %s", cpid, readbuf);
  }

  unlink(path); // delete fifo

  return 0;
}
