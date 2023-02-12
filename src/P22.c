/**
 * CIS3490 - Assignment 2
 * Author: Benjamin Sengupta
 * ID: 1188767
 * Date: 2023-Feb-11
 */

#include "../include/P2utils.h"
#include "../include/utils.h"

// Partitions points of vec from index left to right (exclusive) into S1: points
// that lie on or to the left of the line, and S2: points that lie on the right
// of the line
//
// Returns the start index of S2
unsigned int partition(vector *vec, unsigned int left, unsigned int right,
                       point p1, point p2) {
  if (left == right) return left;

  // Calculate line equation
  double a = p2.y - p1.y;
  double b = p1.x - p2.x;
  double c = p1.x * p2.y - p1.y * p2.x;

  unsigned int fill = left;

  for (unsigned int i = left; i < right; i++) {
    point p3 = vec->items[i];

    // If p3 is to the left or on the line
    if (a * p3.x + b * p3.y < c + DOUBLE_ERROR) {
      // Swap points[i] and points[fill]
      vec->items[i] = vec->items[fill];
      vec->items[fill] = p3;
      fill++;
    }
  }

  return fill;
}

void findhull(vector *hull, vector *vec, unsigned int left, unsigned int right,
              point p1, point p2) {
  if (left == right) return;

  unsigned int farthestIdx = left;
  double largestTriangleArea = 0.0;
  for (unsigned int i = left; i < right; i++) {
    point p3 = vec->items[i];
    // Area will always be negative
    double area = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y -
                  p2.x * p1.y - p1.x * p3.y;
    if (area < largestTriangleArea) {
      largestTriangleArea = area;
      farthestIdx = i;
    }
  }

  // Remove third point from vector and add it to hull
  point p3 = vec->items[farthestIdx];
  vec->items[farthestIdx] = vec->items[right - 1];
  right--;
  vectoradd(hull, p3);

  unsigned int pivot1 = partition(vec, left, right, p1, p3);
  unsigned int pivot2 = partition(vec, left, pivot1, p3, p2);
  findhull(hull, vec, pivot1, right, p1, p3);
  findhull(hull, vec, pivot2, pivot1, p3, p2);
}

// Solution 2: Divide and conquer
// Time Complexity: O(n log n)
vector convexhulldivideandconquer(vector vec) {
  vector hull;
  vectorinit(&hull);

  if (vec.size <= 2) {
    vectorcopy(&hull, &vec);
    return hull;
  }

  // Find index of min and max X elements
  unsigned int minIdx = 0;
  unsigned int maxIdx = 0;
  for (unsigned int i = 1; i < vec.size; i++) {
    if (vec.items[i].x < vec.items[minIdx].x ||
        (vec.items[i].x == vec.items[minIdx].x &&
         vec.items[i].y < vec.items[minIdx].y))
      minIdx = i;
    if (vec.items[i].x > vec.items[maxIdx].x ||
        (vec.items[i].x == vec.items[maxIdx].x &&
         vec.items[i].y > vec.items[maxIdx].y))
      maxIdx = i;
  }

  point A = vec.items[minIdx];
  point B = vec.items[maxIdx];

  vectoradd(&hull, A);
  vectoradd(&hull, B);

  // Swap with end
  unsigned int left = 0;
  unsigned int right = vec.size;

  // Replace minIdx and maxIdx elements with last in vector
  vec.items[minIdx] = vec.items[right - 1];
  vec.items[maxIdx] = vec.items[right - 2];
  right -= 2;

  // Partitions vec into left of or on the line and right of the line
  unsigned int pivotright = partition(&vec, left, right, A, B);
  unsigned int pivotleft = partition(&vec, left, pivotright, B, A);

  findhull(&hull, &vec, pivotleft, pivotright, B, A);
  findhull(&hull, &vec, pivotright, right, A, B);

  hullsortclockwise(hull);

  return hull;
}

int main(void) {
  eval(convexhulldivideandconquer);
  return 0;
}