#include "../include/P2utils.h"

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/utils.h"

float absf(float n) { return (n >= 0) ? n : -n; }
bool floateq(float x1, float x2) { return absf(x1 - x2) < 0.000001; }
bool pointeq(point p1, point p2) {
  return floateq(p1.x, p2.x) && floateq(p1.y, p2.y);
}

bool inboundsf(point boxp1, point boxp2, point p) {
  float minx = (boxp1.x < boxp2.x) ? boxp1.x : boxp2.x;
  float maxx = (boxp1.x > boxp2.x) ? boxp1.x : boxp2.x;
  float miny = (boxp1.y < boxp2.y) ? boxp1.y : boxp2.y;
  float maxy = (boxp1.y > boxp2.y) ? boxp1.y : boxp2.y;

  if (!floateq(minx, p.x) && !floateq(maxx, p.x) && (p.x < minx || p.x > maxx))
    return false;
  if (!floateq(miny, p.y) && !floateq(maxy, p.y) && (p.y < miny || p.y > maxy))
    return false;

  return true;
}

typedef struct pointwithangle {
  point point;
  float angle;
} pointwithangle;

int cmp_pointwithcenter(const void *a, const void *b) {
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
  qsort(pts, vec.size, sizeof(pointwithangle), cmp_pointwithcenter);

  // Finally, write over original vector
  for (unsigned int i = 0; i < vec.size; i++) {
    vec.items[i] = pts[i].point;
  }

  free(pts);
}

void fileread(FILE *file, vector *vec) {
  point p;
  while (fscanf(file, "%f %f", &p.x, &p.y) == 2) {
    vectoradd(vec, p);
  }
}

void eval(algresult (*algorithm)(vector vec)) {
  FILE *file;
  algresult res;
  long int start, end;

  vector vec;
  vectorinit(&vec);

  char filename[BUFFSIZE] = "data_A2_Q2.txt";

  fileopen(filename, &file);
  fileread(file, &vec);
  fclose(file);

  printf("%d points loaded from '%s'\n", vec.size, filename);

  start = millis();
  res = algorithm(vec);
  end = millis();

  printf("Elapsed=%ldms NumPoints=%d Length=%f\n", end - start, res.path.size,
         res.length);
  for (unsigned int i = 0; i < res.path.size; i++) {
    point p = res.path.items[i];
    printf("  %.1f   %.1f\n", p.x, p.y);
  }

  vectorfree(&vec);
  vectorfree(&res.path);
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

void vectorfree(vector *vec) {
  free(vec->items);
  vec->items = NULL;
  vec->capacity = 0;
  vec->size = 0;
}
