#include <stdio.h>

#ifndef P1UTILS_H
#define P1UTILS_H

typedef struct vector {
  unsigned int size;
  unsigned int capacity;
  unsigned long int *items;
} vector;

void vectorinit(vector *vec);
void vectorcopy(vector *dest, vector *src);
void vectoradd(vector *vec, unsigned long int x);
void vectorfree(vector *vec);

void eval(long int (*algorithm)(vector vec));

#endif /* P1UTILS_H */