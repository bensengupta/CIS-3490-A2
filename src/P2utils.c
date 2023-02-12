/**
 * CIS3490 - Assignment 2
 * Author: Benjamin Sengupta
 * ID: 1188767
 * Date: 2023-Feb-11
 */

#include "../include/P2utils.h"

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/utils.h"

inline bool doubleeq(double x1, double x2) {
  return fabs(x1 - x2) < DOUBLE_ERROR;
}

inline bool pointeq(point p1, point p2) {
  return doubleeq(p1.x, p2.x) && doubleeq(p1.y, p2.y);
}

inline double pointdistance(point a, point b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Point with additional angle value
// This struct is exclusively used for quicksort
typedef struct pointwithangle {
  point point;
  double angle;
} pointwithangle;

int cmp_pointwithangle(const void *a, const void *b) {
  const pointwithangle *p1 = a, *p2 = b;
  return (p1->angle > p2->angle) - (p1->angle < p2->angle);
}

void hullsortclockwise(vector vec) {
  if (vec.size == 0) return;

  // Find point with lowest Y
  point lowest = vec.items[0];

  for (unsigned int i = 0; i < vec.size; i++) {
    if (vec.items[i].y < lowest.y) {
      lowest = vec.items[i];
    }
  }

  pointwithangle *pts = malloc(vec.size * sizeof(pointwithangle));

  if (pts == NULL) {
    fprintf(stderr, "error: out of memory\n");
    exit(1);
  }

  for (unsigned int i = 0; i < vec.size; i++) {
    point p = vec.items[i];
    pts[i].point = p;
    // Compute angle relative to lowest Y point
    pts[i].angle =
        p.x == lowest.x ? 0.0 : atan2f(p.y - lowest.y, p.x - lowest.x);
  }

  // Sort with respect to angle
  qsort(pts, vec.size, sizeof(pointwithangle), cmp_pointwithangle);

  // Finally, write over original vector
  for (unsigned int i = 0; i < vec.size; i++) {
    vec.items[i] = pts[i].point;
  }

  free(pts);
}

typedef struct shortestpathresult {
  double pathlength;
  vector path;
} shortestpathresult;

shortestpathresult shortestpath(vector points, int start, int end) {
  point lastPoint;
  double leftlength = 0.0;
  double rightlength = 0.0;

  // ======== Left path ========
  vector leftpath;
  vectorinit(&leftpath);

  lastPoint = points.items[start];

  for (unsigned int i = 0; i < points.size; i++) {
    int idx = (start + points.size - i) % points.size;

    point next = points.items[idx];

    // Add distance to path length
    leftlength += pointdistance(lastPoint, next);
    lastPoint = next;

    // Add next point to path
    vectoradd(&leftpath, next);

    // Stop if end reached
    if (idx == end) break;
  }

  // ======== Right path ========
  vector rightpath;
  vectorinit(&rightpath);

  lastPoint = points.items[start];

  for (unsigned int i = 0; i < points.size; i++) {
    int idx = (start + i) % points.size;

    point next = points.items[idx];

    // Add distance to path length
    rightlength += pointdistance(lastPoint, next);
    lastPoint = next;

    // Add next point to path
    vectoradd(&rightpath, next);

    // Stop if end reached
    if (idx == end) break;
  }

  shortestpathresult res;

  if (leftlength < rightlength) {
    res.path = leftpath;
    res.pathlength = leftlength;
    vectorfree(&rightpath);
  } else {
    res.path = rightpath;
    res.pathlength = rightlength;
    vectorfree(&leftpath);
  }

  return res;
}

void eval(vector (*algorithm)(vector vec)) {
  FILE *file;
  vector hull;
  long int timestart, timeend;

  vector vec;
  vectorinit(&vec);

  char filename[BUFFSIZE] = "data_A2_Q2.txt";

  fileopen(filename, &file);
  fileread(file, &vec);
  fclose(file);

  printf("%d points loaded from '%s'\n", vec.size, filename);

  printf("computing convex hull\n");

  timestart = millis();
  hull = algorithm(vec);
  timeend = millis();

  printf("\n");
  printf("time: %ldms\n", timeend - timestart);
  printf("convex hull (%d points):\n", hull.size);
  vectorprint(hull);
  printf("\n");

  printf("==== compute shortest path ====\n");
  printf("enter coordinates of starting point:\n");
  printf("e.g. 1156.3 24.3\n");
  int idxstart = promptpointindex(hull);
  printf("enter coordinates of ending point:\n");
  int idxend = promptpointindex(hull);
  printf("\n");

  shortestpathresult res = shortestpath(hull, idxstart, idxend);
  printf("shortest path (length: %.1f) (%d points):\n", res.pathlength,
         res.path.size);
  vectorprint(res.path);

  vectorfree(&vec);
  vectorfree(&hull);
  vectorfree(&res.path);
}

unsigned int promptpointindex(vector points) {
  char buffer[BUFFSIZE];

  unsigned int index = 0;
  double x = -1;
  double y = -1;

  while (true) {
    // Prompt for string
    printf("> ");
    readline(buffer);

    // If scanf fails, print error and prompt again
    if (sscanf(buffer, "%lf %lf", &x, &y) != 2) {
      printf("error: invalid input\n");
      continue;
    }

    // Check that point exists
    bool foundPoint = false;
    point p = {x, y};

    for (unsigned int i = 0; i < points.size; i++) {
      if (pointeq(p, points.items[i])) {
        index = i;
        foundPoint = true;
        break;
      }
    }

    // If point was not found, then print error and prompt again
    if (!foundPoint) {
      printf("error: failed to find point\n");
      continue;
    }

    // If all above checks passed, break and return index of point
    break;
  }

  return index;
}

void fileread(FILE *file, vector *vec) {
  point p;
  while (fscanf(file, "%lf %lf", &p.x, &p.y) == 2) {
    vectoradd(vec, p);
  }
}

void vectorinit(vector *vec) {
  vec->size = 0;
  vec->capacity = 0;
  vec->items = NULL;
}

void vectorcopy(vector *dest, vector *src) {
  for (unsigned int i = 0; i < src->size; i++) {
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

void vectorremoveduplicates(vector *vec) {
  unsigned int fill = 0;

  for (unsigned int i = 0; i < vec->size; i++) {
    bool isUnique = true;

    for (unsigned int j = 0; j < fill; j++) {
      if (pointeq(vec->items[i], vec->items[j])) {
        isUnique = false;
        break;
      }
    }

    if (isUnique) {
      vec->items[fill++] = vec->items[i];
    }
  }

  vec->size = fill;
}

void vectorprint(vector vec) {
  int j = (int)(log10(vec.size) + 1);
  int idxwidth = (3 > j) ? 3 : j;

  printf("%*s   %*s  %*s\n", idxwidth, "idx", 6, "x", 6, "y");
  for (unsigned int i = 0; i < vec.size; i++) {
    printf("%*d   %*.1lf  %*.1lf\n", idxwidth, i, 6, vec.items[i].x, 6,
           vec.items[i].y);
  }
}

void vectorfree(vector *vec) {
  free(vec->items);
  vec->items = NULL;
  vec->capacity = 0;
  vec->size = 0;
}
