#include <stdbool.h>
#include <stdio.h>

#ifndef P2UTILS_H
#define P2UTILS_H

#define DOUBLE_ERROR 0.0000001

typedef struct point {
  double x;
  double y;
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
void vectorremoveduplicates(vector *vec);
void vectorfree(vector *vec);
void vectorprint(vector vec);

bool doubleeq(double x1, double x2);
bool pointeq(point p1, point p2);
double pointdistance(point a, point b);
void hullsortclockwise(vector vec);

void eval(vector (*algorithm)(vector vec));

#endif /* P2UTILS_H */