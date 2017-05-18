/*
 * @author Marcin Kołodziej
 * @brief Example with memory mapping
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>     // O_* constants
#include <unistd.h>

struct person_t {
  char name[20];
  char surname[20];
  char job[20];
};

typedef struct db_t {
  int records;
  struct person_t people[50];
} db_t;

static const char shmname[] = "/mmap_db";
static const int  shmsize   = sizeof(db_t);

int main(int argc, char ** argv) {
  if (argc != 2) {
    printf("Usage: %s [client|server]\n", argv[0]);
    exit(0);
  }

  int  shmfd;
  char cmd;

  if (strcmp(argv[1], "client") == 0) {
    printf("Add or Read? ");
    scanf("%c", &cmd);

    db_t * dbptr;

    switch (cmd) {
      case 'r': case 'R':
        shmfd = shm_open(shmname, O_RDONLY, 0755);

        if (shmfd == -1) {
          perror("Failed to open shared memory fd.");
          exit(1);
        }

        dbptr = (db_t *) mmap(NULL, sizeof(db_t), PROT_READ, MAP_SHARED, shmfd, 0);

        if (dbptr == -1) {
          perror("mmap failed");
          close(shmfd);
          exit(1);
        }

        printf("Num|%20s|%20s|%20s|\n", "Name", "Surname", "Job");
        printf("---+--------------------+--------------------+--------------------|\n");
        for (int i = 0; i < dbptr->records; ++i) {
          printf("#%2d|%20s|%20s|%20s|\n",
                  i + 1,
                  dbptr->people[i].name,
                  dbptr->people[i].surname,
                  dbptr->people[i].job);
        }

        munmap(dbptr, sizeof(db_t));
        close(shmfd);
        break;
      case 'a': case 'A':
        shmfd = shm_open(shmname, O_RDWR, 0755);

        if (shmfd == -1) {
          perror("Failed to open shared memory fd");
          exit(1);
        }

        dbptr = (db_t *) mmap(NULL, sizeof(db_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

        if (dbptr == -1) {
          perror("mmap failed");
          close(shmfd);
          exit(1);
        }

        char name[20];
        char surname[20];
        char job[20];

        printf("Name   : ");
        scanf("%s", name);
        printf("Surname: ");
        scanf("%s", surname);
        printf("Job    : ");
        scanf("%s", job);

        if (dbptr->records < 50) {
          strcpy(dbptr->people[dbptr->records].name, name);
          strcpy(dbptr->people[dbptr->records].surname, surname);
          strcpy(dbptr->people[dbptr->records].job, job);
          dbptr->records++;
          printf("Added new record (%s, %s, %s) to database.\n", name, surname, job);
        }
        else {
          printf("Database overflow error!");
        }

        munmap(dbptr, sizeof(db_t));
        close(shmfd);
        break;
      default :
        printf("Wrong command.\n");
        exit(1);
    }
  }
  else if (strcmp(argv[1], "server") == 0) {
    printf("Create or Delete? ");
    scanf("%c", &cmd);

    switch (cmd) {
      case 'c': case 'C':
        shmfd = shm_open(shmname, O_RDWR | O_CREAT | O_TRUNC, 0755);

        if (shmfd == -1) {
          perror("Failed to open/create shared memory fd.");
          exit(1);
        }

        if (ftruncate(shmfd, shmsize) == -1) {
          perror("Failed to truncate shared memory object.");
          exit(1);
        }

        // memory map (shared) database as read-write
        db_t * dbptr = (db_t *) mmap(NULL, sizeof(db_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

        if (dbptr == -1) {
          perror("mmap failed");
          shm_unlink(shmname);
          close(shmfd);
          exit(1);
        }

        // zero the db and insert one record
        // used just like normal pointer to struct
        memset(dbptr, 0, sizeof(struct db_t));
        dbptr->records = 1;
        strcpy(dbptr->people[0].name, "Marcin");
        strcpy(dbptr->people[0].surname, "Kolodziej");
        strcpy(dbptr->people[0].job, "Lecturer");

        close(shmfd);

        printf("Created new database %s.\n", shmname);
        break;
      case 'd': case 'D':
        if (shm_unlink(shmname) == -1) {
          perror("Failed to unlink shared memory fd.");
          exit(1);
        }

        printf("Unlinked database \"%s\".\n", shmname);
        break;
      default :
        printf("Wrong command.\n");
        exit(1);
    }
  }
  else {
    printf("Usage: %s [client|server]\n", argv[0]);
    exit(1);
  }

  return 0;
}