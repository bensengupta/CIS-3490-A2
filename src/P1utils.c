#include "../include/P1utils.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/utils.h"

void fileread(FILE *file, vector *vec) {
  int x;
  while (fscanf(file, "%d", &x) == 1) {
    vectoradd(vec, x);
  }
}

void eval(long int (*algorithm)(vector vec)) {
  FILE *file;
  char buffer[BUFFSIZE];
  vector vec;
  long int inversions;
  long int start, end;

  vectorinit(&vec);

  fileprompt(buffer);
  fileopen(buffer, &file);
  fileread(file, &vec);
  fclose(file);

  printf("%d numbers loaded from '%s'\n", vec.size, buffer);

  start = millis();
  inversions = algorithm(vec);
  end = millis();

  printf("Elapsed=%ldms Inversions=%ld\n", end - start, inversions);

  vectorfree(&vec);
}

void vectorinit(vector *vec) {
  vec->size = 0;
  vec->capacity = 0;
  vec->items = NULL;
}

void vectorcopy(vector *dest, vector *src) {
  for (unsigned int i = 0; i < src->size; i++) {
    vectoradd(dest, src->items[i]);
  }
}

void vectoradd(vector *vec, unsigned long int x) {
  // Increment capacity by one if empty, or double capacity
  if (vec->size == vec->capacity) {
    vec->capacity += (vec->capacity == 0) ? 1 : vec->capacity;
  }
  vec->items = realloc(vec->items, sizeof(unsigned long int) * vec->capacity);

  if (vec->items == NULL) {
    fprintf(stderr, "error: out of memory\n");
    exit(1);
  }

  vec->items[vec->size] = x;
  vec->size++;
}

void vectorfree(vector *vec) {
  free(vec->items);
  vec->items = NULL;
  vec->capacity = 0;
  vec->size = 0;
}
