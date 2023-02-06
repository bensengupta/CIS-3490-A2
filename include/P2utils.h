#include <stdbool.h>
#include <stdio.h>

#ifndef P2UTILS_H
#define P2UTILS_H

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

typedef struct algresult {
  float length;
  vector path;
} algresult;

float absf(float n);
bool floateq(float x1, float x2);
bool pointeq(point p1, point p2);
bool inboundsf(point boxp1, point boxp2, point p);
void hullsortclockwise(vector vec);

void eval(algresult (*algorithm)(vector vec));

#endif /* P2UTILS_H */