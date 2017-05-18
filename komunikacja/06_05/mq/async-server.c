/*
 * @author Marcin Kołodziej
 * @brief Simple async mq server
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <mqueue.h>
#include <pthread.h> // for threads

static void handle_notification(union sigval sv);

// function to register to notification
void register_mq(mqd_t* mqd) {
  struct sigevent sev; // structure for handling signal
  sev.sigev_notify            = SIGEV_THREAD;        // run handler in new thread
  sev.sigev_notify_function   = handle_notification; // register handler
  sev.sigev_notify_attributes = NULL;                // no attributes
  sev.sigev_value.sival_ptr   = mqd;                 // argument for handler

  if (mq_notify(*mqd, &sev) == -1) {
    printf("Error on notification registration!\n");
    exit(1);
  }
}

// notification handler that will be run in separate thread
static void handle_notification(union sigval sv) {
  struct mq_attr attr;    // attribute struct to get msg number and size
  ssize_t        nr;      // variable to store number of msgs in mq
  char *         readbuf; // buffer to be allocated
  unsigned       prio;    // message priority
  int            cmp;     // variable for strcmp

  mqd_t mqd = *((mqd_t *) sv.sival_ptr); // get descriptor for mq

  mq_getattr(mqd, &attr); // get msg size

  readbuf = malloc(attr.mq_msgsize); // allocate buffer
  memset(readbuf, 0, attr.mq_msgsize);

  nr = mq_receive(mqd, readbuf, attr.mq_msgsize, &prio); // get msg
  if (nr == -1) {
    printf("No messages in queue!\n");
    exit(1); // terminate with error
  }

  printf("Read %zd bytes, msgprio(%d): %s\n", nr, prio, readbuf);

  cmp = strcmp(readbuf, "quit");
  free(readbuf);

  if (cmp != 0) {
    register_mq(sv.sival_ptr);
  }
  else {
    mq_close(mqd);
    mq_unlink("/wizut-ipc-async");
    exit(0); // terminate the process successfully
  }
}

int main(int argc, char** argv) {
  mqd_t           mqd; // message queue descriptor

  mqd = mq_open("/wizut-ipc-async", O_RDWR | O_CREAT, 666, 0);

  if (mqd == -1) {
    printf("Error on opening mq: %s\n", strerror(errno));
    exit(1);
  }

  register_mq(&mqd);

  pause(); // pause this thread
           // process will be terminated by notification handler
}
