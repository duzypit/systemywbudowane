/*
 * @author Marcin Kołodziej
 * @brief FIFO mkfifoat example
 */

#include <stdio.h>
#include <string.h>

#include <stdlib.h>    // exit
#include <unistd.h>    // read,write
#include <sys/types.h> // open
#include <sys/stat.h>  // mkfifoat
#include <fcntl.h>     // open flags
#include <dirent.h>    // directory operations

int main (int argc, char** argv) {
  int   fd;     // file descriptor
  int   bytes;  // read bytes
  pid_t cpid;   // child process id
  char  msg[] = "Message from the other process via FIFO!\n";
  char  path[] = "example_mkfifoat";
  int   dirfd;
  char  readbuf[255];

  dirfd = open("/tmp", O_DIRECTORY);

  mkfifoat(dirfd, path, 0666); // create fifo
                               // 666 == rw-rw-rw-

  cpid = fork();

  if (cpid == -1) {
    // on error
    perror("fork");
    exit(1);
  }

  if (cpid == 0) {
    // child process
    fd = openat(dirfd, path, O_WRONLY);
    write(fd, msg, strlen(msg) + 1);
    close(fd);
    close(dirfd);
    exit(0);
  }
  else {
    // parent process
    fd = openat(dirfd, path, O_RDONLY);
    bytes = read(fd, readbuf, sizeof(readbuf));
    close(fd);
    close(dirfd);
    printf("Received string from child(pid %x): %s", cpid, readbuf);
  }

  unlink(path); // delete fifo

  return 0;
}
