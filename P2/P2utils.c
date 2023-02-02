#include "P2utils.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fileread(FILE *file, vector *vec) {
  int x;
  while (fscanf(file, "%d", &x) == 1) {
    vectoradd(vec, x);
  }
}

void vectorinit(vector *vec) {
  vec->size = 0;
  vec->capacity = 0;
  vec->nums = NULL;
}

void vectorcopy(vector *dest, vector *src) {
  for (int i = 0; i < src->size; i++) {
    vectoradd(dest, src->nums[i]);
  }
}

void vectoradd(vector *vec, unsigned long int x) {
  // Increment capacity by one if empty, or double capacity
  if (vec->size == vec->capacity) {
    vec->capacity += (vec->capacity == 0) ? 1 : vec->capacity;
  }
  vec->nums = realloc(vec->nums, sizeof(unsigned long int) * vec->capacity);

  if (vec->nums == NULL) {
    fprintf(stderr, "error: out of memory\n");
    exit(1);
  }

  vec->nums[vec->size] = x;
  vec->size++;
}

void vectorfree(vector *vec) {
  free(vec->nums);
  vec->nums = NULL;
  vec->capacity = 0;
  vec->size = 0;
}
