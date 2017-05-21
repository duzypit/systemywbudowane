/*
 * @author Marcin Kołodziej
 * @brief Mmap with semaphores example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

static const char shmlogger[]  = "/shm_logger";

static const char semmutex[]   = "/sem_mutex";
static const char sembufferc[] = "/sem_buffer_count";
static const char semprinter[] = "/sem_printer";

static const int  buffernum  = 10;
static const int  buffersize = 256;

typedef struct logs_t {
  int write_index;
  int print_index;
  char logs[10][256];
} logs_t;


void error(char * msg) {
  perror(msg);
  exit(1);
}

void sig_handler(int signo) {
  if (signo = SIGINT) {
    printf("Stopping application.\n");
    shm_unlink(shmlogger);
    sem_unlink(semmutex);
    sem_unlink(sembufferc);
    sem_unlink(semprinter);
    exit(0);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    printf("Usage: %s [num of child processes]\n", argv[0]);
    exit(1);
  }

  if (signal(SIGINT, sig_handler) == SIG_ERR) {
    error("Can't catch SIGINT");
  }

  pid_t cpid;
  int   cnum = strtol(argv[1], 0, 10);

  sem_t * mutex_sem;
  sem_t * bufferc_sem;
  sem_t * printer_sem;

  logs_t * logs_ptr;

  int shmfd;

  printf("Spawning children...\n");
  for (int i = 0; i < cnum; ++i) {
    cpid = fork();

    if (cpid == -1) {
      error("fork");
    }

    if (cpid == 0) {
      // child process
      break;
    }

    printf("Spawned child process (%d of %d) with pid(%d)\n", i + 1, cnum, cpid);
  }

  if (cpid != 0) {
    // parent (server) process

    printf("Preparing semaphores...\n");
    mutex_sem = sem_open(semmutex, O_CREAT, 0666, 0);
    if (mutex_sem == SEM_FAILED) {
      error("sem_open mutex");
    }

    bufferc_sem = sem_open(sembufferc, O_CREAT, 0666, buffernum);
    if (bufferc_sem == SEM_FAILED) {
      error("sem_open bufferc");
    }

    printer_sem = sem_open(semprinter, O_CREAT, 0666, 0);
    if (printer_sem == SEM_FAILED) {
      error("sem_open pritner");
    }

    printf("Opening shared memory object...\n");
    shmfd = shm_open(shmlogger, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (shmfd == -1) {
      error("shm_open");
    }

    printf("Truncating shared memory object...\n");
    if (ftruncate(shmfd, sizeof(logs_t)) == -1) {
      error("ftruncate");
    }

    printf("Mmaping shared memory object...\n");
    logs_ptr = (logs_t *) mmap(NULL, sizeof(logs_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (logs_ptr == -1) {
      error("mmap");
    }

    printf("Zeroing shared memory object...\n");
    memset(logs_ptr, 0, sizeof(logs_t));

    printf("Setting mutex semaphore to indicate end of initalization...\n");
    if (sem_post(mutex_sem) == -1) {
      error("sem_post mutex");
    }

    fflush(stdout);

    printf("Initialization complete!\n");
    char readbuf[buffersize];

    for (;;) {
      memset(readbuf, 0, buffersize);

      if (sem_wait(printer_sem) == -1) {
        error("sem_wait printer");
      }

      strcpy(readbuf, logs_ptr->logs[logs_ptr->print_index]);
      logs_ptr->print_index++;

      if (logs_ptr->print_index == buffernum) {
        logs_ptr->print_index = 0;
      }

      if (sem_post(bufferc_sem) == -1) {
        error("sem_post buffer count");
      }

      printf("%s\n", readbuf);
    }
  }

  if (cpid == 0) {
    // child process
    sleep(1);
    pid_t ownpid = getpid();
    mutex_sem = sem_open(semmutex, 0, 0, 0);
    if (mutex_sem == SEM_FAILED) {
      error("child sem_open mutex");
    }
    bufferc_sem = sem_open(sembufferc, 0, 0, 0);
    if (bufferc_sem == SEM_FAILED) {
      error("child sem_open bufferc");
    }
    printer_sem = sem_open(semprinter, 0, 0, 0);
    if (printer_sem == SEM_FAILED) {
      error("child sem_open pritner");
    }
    shmfd = shm_open(shmlogger, O_RDWR, 0);
    if (shmfd == -1) {
      error("child shm_open");
    }
    logs_ptr = (logs_t *) mmap(NULL, sizeof(logs_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (logs_ptr == -1) {
      error("child mmap");
    }

    for(int i = 0; i < 10; ++i) {
      if (sem_wait(bufferc_sem) == -1) {
        error("child sem_wait buffer count");
      }

      if (sem_wait(mutex_sem) == -1) {
        error("child sem_wait mutex");
      }

      // CRITICAL SECTION BEGIN
      sprintf(logs_ptr->logs[logs_ptr->write_index], "pid(%d) loop %d out of 10", ownpid, i);
      logs_ptr->write_index++;

      if (logs_ptr->write_index == buffernum) {
        logs_ptr->write_index = 0;
      }
      // CRITICAL SECTION END

      if (sem_post(mutex_sem) == -1) {
        error("child sem_post mutex");
      }

      if (sem_post(printer_sem) == -1) {
        error("child sem_post buffer count");
      }

      sleep(ownpid % 10 + 1);
    }

    if (munmap(logs_ptr, sizeof(logs_t)) == -1) {
      error("child munmap");
    }

    close(shmfd);
  }

  return 0;
}