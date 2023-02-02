#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readline(char buffer[BUFFSIZE]) {
  fgets(buffer, BUFFSIZE, stdin);
  buffer[strlen(buffer) - 1] = '\0';
}

void fileprompt(char buffer[BUFFSIZE]) {
  printf("file: ");
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

void vectorprint(vector vec) {
  printf("debug: vec[%ld, %ld, %ld, ..., %ld]\n", vec.nums[0], vec.nums[1],
         vec.nums[2], vec.nums[vec.size - 1]);
  printf("debug: size %d\n", vec.size);
}

long int timems() { return clock() / (CLOCKS_PER_SEC / 1000); }