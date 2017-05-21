/*
 * @author Marcin Kołodziej
 * @brief Open shared memory segment example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>     // O_* constants
#include <unistd.h>

static const char shmname[] = "/shm_example";
static const char msg[]     = "This is  my example.";
static const int  fsize     = sizeof(msg);

int main(int argc, char ** argv) {
  int shmfd; // shared memory file descriptor

  // read-write, create on open, if exist truncate to 0B
  shmfd = shm_open(shmname, O_WRONLY | O_CREAT | O_TRUNC, 0755);

  if (shmfd == -1) {
    perror("Failed to open/create shared memory fd.");
    exit(1);
  }

  printf("Created shared memory object\"%s\".\n", shmname);

  // resize shared memory object to the size of the message
  if (ftruncate(shmfd, fsize) == -1) {
    perror("Failed to truncate shared memory object.");
    exit(1);
  }

  printf("Truncated shared memory object to %d bytes.\n", fsize);

  if (write(shmfd, msg, fsize) == -1) {
    perror("Failed to write to shared memory fd.");
    exit(1);
  }

  close(shmfd);
  printf("Written \"%s\" to shared memory fd.\n", msg);

  return 0;
}