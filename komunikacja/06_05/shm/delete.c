/*
 * @author Marcin Kołodziej
 * @brief Delete shared memory segment example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

static const char shmname[] = "/shm_example";

int main(int argc, char ** argv) {
  int shmfd; // shared memory file descriptor
  char readbuf[255];

  // read-only
  shmfd = shm_open(shmname, O_RDONLY, 0755);

  if (shmfd == -1) {
    perror("Failed to open shared memory fd.");
    exit(1);
  }

  if (read(shmfd, readbuf, sizeof(readbuf)) == -1) {
    perror("Failed to open shared memory fd.");
    exit(1);
  }

  printf("Read from shared memory: %s\n", readbuf);

  // delete shared memory object
  if (shm_unlink(shmname) == -1) {
    perror("Failed to unlink shared memory fd.");
    exit(1);
  }

  close(shmfd);
  printf("Unlinked shared object \"%s\".\n", shmname);

  return 0;
}