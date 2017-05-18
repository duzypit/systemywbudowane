/*
 * @author Marcin Kołodziej
 * @brief Using mq attributes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <mqueue.h>

int main(int argc, char** argv) {
  struct mq_attr old_attr;           // old attributes storage
  struct mq_attr new_attr;       // new attributes
  mqd_t          mqd;            // message queue descriptor
  char           readbuf[4096];  // read buffer

  mqd = mq_open("/wizut-ipc", O_RDWR | O_CREAT, 0666, 0);

  if (mqd == -1) {
    printf("Error on opening mq: %s\n", strerror(errno));
    exit(1);
  }

  // new attributes
  new_attr.mq_flags   = O_NONBLOCK; // nonblocking queue
  new_attr.mq_maxmsg  = 15;         // maximum number of msgs in queue
  new_attr.mq_msgsize = 256;        // maximum msg size
  new_attr.mq_curmsgs = 5;          // current number of msgs
  // only flags can be modified!

  if (mq_setattr(mqd, &new_attr, &old_attr) == -1) {
    mq_close(mqd);
    mq_unlink("/wizut-ipc");
    printf("Couldn't change settings: %s\n", strerror(errno));
    exit(1);
  }

  if (mq_getattr(mqd, &new_attr) == -1) {
    mq_close(mqd);
    mq_unlink("/wizut-ipc");
    printf("Couldn't change settings: %s\n", strerror(errno));
    exit(1);
  }

  printf("old vs new attributes:\n mq_flags = %ld | %ld\n mq_maxmsq = %ld | %ld\n mq_msgsize = %ld | %ld bytes\n mq_curmsgs = %ld | %ld\n",
        old_attr.mq_flags,   new_attr.mq_flags,
        old_attr.mq_maxmsg,  new_attr.mq_maxmsg,
        old_attr.mq_msgsize, new_attr.mq_msgsize,
        old_attr.mq_curmsgs, new_attr.mq_curmsgs);

  for (int i = 0; i < 15; ++i) {
    char buf[512];
    memset(buf, 'a', 512);
    int res = mq_send(mqd, buf, 512, 0);
    printf("Sending msg#%d... Result: %d (%s)\n", i, res, strerror(errno));
  }

  mq_close(mqd);           // close mq
  mq_unlink("/wizut-ipc"); // delete "wizut-ipc" mq
}
