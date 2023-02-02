#include "utils.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readline(char buffer[BUFFSIZE]) {
  fgets(buffer, BUFFSIZE, stdin);
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

unsigned int optionprompt(unsigned int count, option *options) {
  for (int i = 0; i < count; i++) {
    printf("[%s] %s\n", options[i][0], options[i][1]);
  }

  char buffer[BUFFSIZE];

  while (true) {
    printf("> ");
    readline(buffer);

    for (unsigned int i = 0; i < count; i++) {
      if (strcmp(buffer, options[i][0]) == 0) {
        return i;
      }
    }

    printf("error: invalid input, try again\n");
  }
}

long int timems() { return (1000 * clock()) / CLOCKS_PER_SEC; }