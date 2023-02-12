/**
 * CIS3490 - Assignment 2
 * Author: Benjamin Sengupta
 * ID: 1188767
 * Date: 2023-Feb-11
 */

#include <stdio.h>

#ifndef P1UTILS_H
#define P1UTILS_H

// Growable array
typedef struct vector {
  unsigned int size;
  unsigned int capacity;
  unsigned long int *items;
} vector;

void vectorinit(vector *vec);
void vectorcopy(vector *dest, vector *src);
void vectoradd(vector *vec, unsigned long int x);
void vectorfree(vector *vec);

// Evaluate a counting inversion algorithm
void eval(long int (*algorithm)(vector vec));

#endif /* P1UTILS_H */