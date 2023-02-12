/**
 * CIS3490 - Assignment 2
 * Author: Benjamin Sengupta
 * ID: 1188767
 * Date: 2023-Feb-11
 */

#include "../include/P1utils.h"
#include "../include/utils.h"

// Solution 1: Brute Force
// Time Complexity: O(n^2)
long int bruteforceinversions(vector vec) {
  long int inversions = 0;

  for (unsigned int i = 0; i < vec.size; i++) {
    for (unsigned int j = i + 1; j < vec.size; j++) {
      if (vec.items[i] > vec.items[j]) {
        inversions++;
      }
    }
  }

  return inversions;
}

int main(void) {
  eval(bruteforceinversions);
  return 0;
}