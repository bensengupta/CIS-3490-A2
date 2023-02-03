#include "../include/P2utils.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/utils.h"

void fileread(FILE *file, vector *vec) {
  point p;
  while (fscanf(file, "%f %f", &p.x, &p.y) == 2) {
    vectoradd(vec, p);
  }
}

void eval(algresult (*algorithm)(vector vec)) {
  FILE *file;
  vector vec;
  algresult res;
  long int start, end;

  vectorinit(&vec);

  char filename[] = "data_A2_Q2.txt";

  fileopen(filename, &file);
  fileread(file, &vec);
  fclose(file);

  printf("%d points loaded from '%s'\n", vec.size, filename);

  start = millis();
  res = algorithm(vec);
  end = millis();

  printf("Elapsed=%ldms NumPoints=%d Length=%f\n", end - start, res.path.size,
         res.length);
  for (int i = 0; i < res.path.size; i++) {
    point p = res.path.items[i];
    printf("  Point %.1f %.1f\n", p.x, p.y);
  }

  vectorfree(&vec);
}

void vectorinit(vector *vec) {
  vec->size = 0;
  vec->capacity = 0;
  vec->items = NULL;
}

void vectorcopy(vector *dest, vector *src) {
  for (int i = 0; i < src->size; i++) {
    vectoradd(dest, src->items[i]);
  }
}

void vectoradd(vector *vec, point p) {
  // Increment capacity by one if empty, or double capacity
  if (vec->size == vec->capacity) {
    vec->capacity += (vec->capacity == 0) ? 1 : vec->capacity;
  }
  vec->items = realloc(vec->items, sizeof(point) * vec->capacity);

  if (vec->items == NULL) {
    fprintf(stderr, "error: out of memory\n");
    exit(1);
  }

  vec->items[vec->size] = p;
  vec->size++;
}

void vectorfree(vector *vec) {
  free(vec->items);
  vec->items = NULL;
  vec->capacity = 0;
  vec->size = 0;
}
