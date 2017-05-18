/*
 * @author Marcin Kołodziej
 * @brief Usage of mq with priority
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <mqueue.h>

int main(int argc, char** argv) {
  struct mq_attr attr;           // attributes storage
  mqd_t          mqd;            // message queue descriptor
  char           readbuf[10240]; // read buffer
                                 // must be bigger than max msg size

  // open mq named "wizut-ipc"
  // read / write
  // file permissions rw-rw-r--
  // default attributes
  mqd = mq_open("/wizut-ipc", O_RDWR | O_CREAT, 644, 0);

  if (mqd == -1) {
    printf("Error on opening mq: %s\n", strerror(errno));
  }

  char msg[] = "Message";
  // insert some messages with mixed priority
  for (int i = 0; i < 5; ++i) {
    printf("Send msg(%s) with prio(%d)\n", msg, i);
    mq_send(mqd, msg, sizeof(msg), i);
    printf("Send msg(%s) with prio(%d)\n", msg, 9 - i);
    mq_send(mqd, msg, sizeof(msg), 9 - i);
  }

  // read messages
  for (int i = 0; i < 10; ++i) {
    int prio;
    memset(readbuf, 0, sizeof(readbuf));
    mq_receive(mqd, readbuf, sizeof(readbuf), &prio);
    printf("Received msg(%s) with prio(%d)\n", readbuf, prio);
  }

  mq_close(mqd);           // close mq
  mq_unlink("/wizut-ipc"); // delete "wizut-ipc" mq
}
