#include "../include/utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readline(char buffer[BUFFSIZE]) {
  if (fgets(buffer, BUFFSIZE, stdin) == NULL) {
    fprintf(stderr, "error: failed to read from stdin\n");
    exit(1);
  }
  buffer[strlen(buffer) - 1] = '\0';
}

void fileprompt(char buffer[BUFFSIZE]) {
  printf("filename:\n> ");
  readline(buffer);
}

void fileopen(char filename[BUFFSIZE], FILE **fp) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "error: file \"%s\" not found\n", filename);
    exit(1);
  }

  *fp = file;
}

long int millis() { return (1000 * clock()) / CLOCKS_PER_SEC; }

int promptint(int min, int max) {
  char buffer[BUFFSIZE];

  int inp = -1;

  printf("> ");
  while (true) {
    readline(buffer);
    if (sscanf(buffer, "%d", &inp) == 1 && inp >= min && inp <= max) break;
    printf("error: invalid input\n");
    printf("> ");
  }

  return inp;
}