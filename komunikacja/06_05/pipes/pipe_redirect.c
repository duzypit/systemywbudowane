/*
 * @author Marcin Kołodziej
 * @brief simple stream redirection example
 */

#include <stdio.h>

#include <stdlib.h> // exit
#include <unistd.h> // pipe, read, write

int main (int argc, char** argv) {
  if (argc > 1) {
    dup2(1, 2); // create a copy of first fd
                // and assign it to second fd
                // in this case redirect stderr to stdout

    // same as following code:
    // close(2);
    // dup(1);
  }

  fprintf(stderr, "This is an error.\n");
  fprintf(stdout, "This is a message.\n");

  return 0;
}
