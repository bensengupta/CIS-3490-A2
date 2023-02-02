#include <stdio.h>
#include <time.h>

typedef struct vector {
  unsigned int size;
  unsigned int capacity;
  unsigned long int *nums;
} vector;

void fileread(FILE *file, vector *vec);

void vectorinit(vector *vec);
void vectorcopy(vector *dest, vector *src);
void vectoradd(vector *vec, unsigned long int x);
void vectorfree(vector *vec);
long int timems();