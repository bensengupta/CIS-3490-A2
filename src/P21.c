/**
 * CIS3490 - Assignment 2
 * Author: Benjamin Sengupta
 * ID: 1188767
 * Date: 2023-Feb-11
 */

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../include/P2utils.h"
#include "../include/utils.h"

// Solution 1: Brute Force
// Time Complexity: O(n^2)
vector convexhullbruteforce(vector vec) {
  vector path;
  vectorinit(&path);

  for (unsigned int i = 0; i < vec.size; i++) {
    for (unsigned int j = 0; j < vec.size; j++) {
      // Are points p1 and p2 on the convex hull?
      point p1 = vec.items[i];
      point p2 = vec.items[j];

      // Calculate line equation between p1 and p2
      double a = p2.y - p1.y;
      double b = p1.x - p2.x;
      double c = p1.x * p2.y - p1.y * p2.x;

      bool isHullSegment = true;

      // Integer representing which side all points are on
      // 1 = Greater than
      // -1 = Lesser than
      // 0 = Undecided
      int side = 0;

      // Ensure that all points lie on one side of the hull before adding
      // p1 and p2 to the list of hull points
      for (unsigned int k = 0; k < vec.size; k++) {
        point pk = vec.items[k];
        double lhs = a * pk.x + b * pk.y;

        // Case 1: Point K is greater than the line
        if (lhs > c + DOUBLE_ERROR) {
          if (side == -1) {
            isHullSegment = false;
            break;
          }
          side = 1;
          // Case 2: Point K is lesser than the line
        } else if (lhs < c - DOUBLE_ERROR) {
          if (side == 1) {
            isHullSegment = false;
            break;
          }
          side = -1;
        } else {
          // Case 3: Point K is on the affine line of p1 to p2
          // P1 and P2 are valid hull points only if pk is between them
          if (fmin(p1.x, p2.x) <= pk.x && pk.x <= fmax(p1.x, p2.x) &&
              fmin(p1.y, p2.y) <= pk.y && pk.y <= fmax(p1.y, p2.y))
            continue;
          isHullSegment = false;
          break;
        }
      }

      if (isHullSegment) {
        vectoradd(&path, p1);
        break;
      }
    }
  }

  vectorremoveduplicates(&path);
  hullsortclockwise(path);

  return path;
}

int main(void) {
  eval(convexhullbruteforce);
  return 0;
}