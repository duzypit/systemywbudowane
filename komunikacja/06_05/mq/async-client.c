/*
 * @author Marcin Kołodziej
 * @brief Simple async mq client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <mqueue.h>

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Usage: %s [msg] [prio]\n", argv[0]);
    return 0;
  }

  mqd_t  mqd;
  char * msg = argv[1];
  int    prio = strtol(argv[2], 0, 10);

  // open mq named "wizut-ipc-async" as write-only
  mqd = mq_open("/wizut-ipc-async", O_WRONLY);

  if (mqd == -1) {
    printf("Error on opening mq: %s\n", strerror(errno));
    exit(1);
  }

  if (mq_send(mqd, msg, strlen(msg), prio) == -1) {
    printf("Sent message \"%s\" with prio %d.\n", msg, prio);
  }

  mq_close(mqd);

  return 0;
}
