/**
 * CIS3490 - Assignment 2
 * Author: Benjamin Sengupta
 * ID: 1188767
 * Date: 2023-Feb-11
 */

#include <stdbool.h>
#include <stdio.h>

#ifndef P2UTILS_H
#define P2UTILS_H

// Margin of error for double equality checks
#define DOUBLE_ERROR 0.000001

typedef struct point {
  double x;
  double y;
} point;

// Growable array
typedef struct vector {
  unsigned int size;
  unsigned int capacity;
  point *items;
} vector;

// Read a file into a vector
void fileread(FILE *file, vector *vec);

void vectorinit(vector *vec);
void vectorcopy(vector *dest, vector *src);
void vectoradd(vector *vec, point p);
void vectorfree(vector *vec);
void vectorprint(vector vec);
// Remove duplicates in vector
// Time Complexity: Θ(n^2)
void vectorremoveduplicates(vector *vec);

// Double equality check
bool doubleeq(double x1, double x2);

// Point equality check
bool pointeq(point p1, point p2);

// Returns the distance of a to b
double pointdistance(point a, point b);

// Sorts hull points clockwise
void hullsortclockwise(vector vec);

// Prompt the user to select a point among a list of points
unsigned int promptpointindex(vector points);

// Evaluate a convex hull algorithm
void eval(vector (*algorithm)(vector vec));

#endif /* P2UTILS_H */