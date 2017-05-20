/*
 * @author Marcin Kołodziej
 * @brief MQ creation
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
  char           readbuf[4096];  // read buffer

  // open mq named "wizut-ipc"
  // read / write
  // file permissions rw-rw-r--
  // default attributes
  mqd = mq_open("/wizut-ipc", O_RDWR | O_CREAT, 666, 0);

  if (mqd == -1) {
    printf("Error on opening mq: %s\n", strerror(errno));
  }

  mq_getattr(mqd, &attr); // read mq attributes

  // print the default attributes
  // note: mq_flags can be either 0 or O_NONBLOCK
  printf("default attributes:\n mq_flags = %ld\n mq_maxmsq = %ld\n mq_msgsize = %ld bytes\n mq_curmsgs = %ld\n",
        attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

  mq_close(mqd);           // close mq
  mq_unlink("/wizut-ipc"); // delete "wizut-ipc" mq
}
