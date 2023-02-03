#include <stdio.h>
#include <time.h>

typedef struct point {
  float x;
  float y;
} point;

typedef struct vector {
  unsigned int size;
  unsigned int capacity;
  point *items;
} vector;

void fileread(FILE *file, vector *vec);

void vectorinit(vector *vec);
void vectorcopy(vector *dest, vector *src);
void vectoradd(vector *vec, point p);
void vectorfree(vector *vec);
long int timems();