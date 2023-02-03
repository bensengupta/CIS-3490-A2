#include "../include/P1utils.h"
#include "../include/utils.h"

// Solution 1: Brute Force
// Time Complexity: O(n^2)
long int bruteforceinversions(vector vec) {
  long int inversions = 0;

  for (int i = 0; i < vec.size; i++) {
    for (int j = i + 1; j < vec.size; j++) {
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