#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../include/P2utils.h"
#include "../include/utils.h"

// Solution 1: Brute Force
// Time Complexity: O(n^2)
algresult convexhullbruteforce(vector vec) {
  vector path;
  vectorinit(&path);

  for (unsigned int i = 0; i < vec.size; i++) {
    for (unsigned int j = 0; j < vec.size; j++) {
      // The purpose of the below code is to determine if p1 is part of the
      // convex hull
      point p1 = vec.items[i];
      point p2 = vec.items[j];

      // Calculate line equation
      double a = p2.y - p1.y;
      double b = p1.x - p2.x;
      double c = p1.x * p2.y - p1.y * p2.x;

      bool isHullSegment = true;

      // Integer representing which side all points are on
      // 1 = Greater than
      // -1 = Lesser than
      // 0 = Undecided
      int side = 0;

      // Check that all points lie on one side of the hull
      for (unsigned int k = 0; k < vec.size; k++) {
        point pk = vec.items[k];
        double lhs = a * pk.x + b * pk.y;

        // doubleeq(lhs, c) means a * x + b * y == c and pk is on the line
        if (doubleeq(lhs, c)) {
          // Skip if point K is overlapping with point I or J
          if (pointeq(pk, p1)) continue;
          if (pointeq(pk, p2)) continue;
          // Skip if point I is not in between point J and K
          if (p1.x < fmin(p2.x, pk.x) || fmax(p2.x, pk.x) < p1.x ||
              p1.y < fmin(p2.y, pk.y) || fmax(p2.y, pk.y) < p1.y)
            continue;
          isHullSegment = false;
          break;
          // lhs > c means p is greater than the line
        } else if (lhs > c) {
          if (side == -1) {
            isHullSegment = false;
            break;
          }
          side = 1;
          // lhs < c means p is less than the line
        } else {
          if (side == 1) {
            isHullSegment = false;
            break;
          }
          side = -1;
        }
      }

      if (isHullSegment) {
        vectoradd(&path, vec.items[i]);
        break;
      }
    }
  }

  // Remove duplicate points in the path
  vector unique;
  vectorinit(&unique);

  for (unsigned int i = 0; i < path.size; i++) {
    bool isUnique = true;

    point p1 = path.items[i];

    for (unsigned int j = i + 1; j < path.size; j++) {
      point p2 = path.items[j];

      if (pointeq(p1, p2)) {
        isUnique = false;
        break;
      };
    }

    if (isUnique) {
      vectoradd(&unique, path.items[i]);
    }
  }

  vectorfree(&path);

  hullsortclockwise(unique);

  algresult res = {0.0, unique};

  return res;
}

int main(void) {
  eval(convexhullbruteforce);
  return 0;
}